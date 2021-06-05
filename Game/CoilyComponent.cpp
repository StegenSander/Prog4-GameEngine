#include "MiniginPCH.h"
#include "CoilyComponent.h"
#include "GameControllerComponent.h"
#include "LevelNavigatorComponent.h"
#include "GameTime.h"
#include "BlockComponent.h"
#include "TextureComponent.h"
#include "ExtraMath.h"
#include "ScoreComponent.h"
#include "Scene.h"
#include "QBertComponent.h"
#include "ServiceLocator.h"


CoilyComponent::CoilyComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
	, const std::weak_ptr<GameControllerComponent>& pGameController
	, const std::weak_ptr<TextureComponent>& pTexture
	, int spawnIndex, float timeBetweenMoves)
	: EntityComponent(pGameController,EntityType::Coily)
	, m_SpawnIndex(spawnIndex)
	, m_pNavigator{pNavigator}
	, m_pTexture{pTexture}
	, m_TimeBetweenMoves{timeBetweenMoves}
{
	m_TimeUntilNextMove = m_TimeBetweenMoves;
}

CoilyComponent::~CoilyComponent()
{
}

void CoilyComponent::Update()
{
	float deltaTime = GameTime::GetInstance().GetDeltaTime();
	m_TimeUntilNextMove -= deltaTime;
	if (m_TimeUntilNextMove < 0)
	{
		if (!m_HasTransformed) //Egg Movement
		{
			EggMove();
		}
		else //Coily movement (chase player)
		{
			m_pQBertNavigator = GetClosestQBert();
			if (!m_pQBertNavigator.expired())
			{
				
			}
		}

		m_TimeUntilNextMove = m_TimeBetweenMoves;
	}
}

void CoilyComponent::EggMove()
{
	bool moveLeft = static_cast<bool>(rand() % 2); //is 0 or 1

	MoveResult moveResult;
	if (moveLeft) moveResult = m_pNavigator.lock()->Move(Direction::SouthWest, this);
	else moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);

	if (moveResult.BlockOccupied)
	{
		moveLeft = !moveLeft;
		if (moveLeft) moveResult = m_pNavigator.lock()->Move(Direction::SouthWest, this);
		else moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);
	}

	if (!moveResult.ValidMove) Transform(false);
}

void CoilyComponent::CoilyMove()
{
	int targetRow = 0;
	int targetCol = 0;
	if (m_IsMovingToTarget) // moving to specified target
	{
		targetRow = m_TargetRow;
		targetCol = m_TargetColumn;
	}
	else //chasing Qbert
	{
		targetRow = m_pQBertNavigator.lock()->GetCurrentRow();
		targetCol = m_pQBertNavigator.lock()->GetCurrentColumn();
	}

	int coilyRow = m_pNavigator.lock()->GetCurrentRow();
	int coilyCol = m_pNavigator.lock()->GetCurrentColumn();
	const int distanceToTargetStart = ExtraMath::DistanceFromTo(coilyRow, coilyCol, targetRow, targetCol);


	const int rowDif = targetRow - coilyRow;
	const int colDif = targetCol - coilyCol;
	if (abs(rowDif) + abs(colDif) == 0 && m_IsMovingToTarget) m_IsMovingToTarget = false;

	//Actually move
	MoveResult moveResult;
	if (colDif == 0 && rowDif < 0)
	{
		m_pNavigator.lock()->Move(Direction::NorthEast, this);
	}
	else if (colDif == 0 && rowDif > 0)
	{
		m_pNavigator.lock()->Move(Direction::SouthWest, this);
	}
	else if (rowDif <= 0 && colDif > 0)
	{
		moveResult = m_pNavigator.lock()->Move(Direction::NorthEast, this);
		if (moveResult.BlockOccupied || !moveResult.ValidMove)
			moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);
	}
	else if (rowDif < 0 && colDif < 0)
	{
		moveResult = m_pNavigator.lock()->Move(Direction::NorthWest, this);
		if (moveResult.BlockOccupied || !moveResult.ValidMove)
			moveResult = m_pNavigator.lock()->Move(Direction::NorthEast, this);
	}
	else if (rowDif > 0 && colDif > 0)
	{
		moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);
		if (moveResult.BlockOccupied || !moveResult.ValidMove)
			moveResult = m_pNavigator.lock()->Move(Direction::SouthWest, this);
	}
	else if (rowDif >= 0 && colDif < 0)
	{
		moveResult = m_pNavigator.lock()->Move(Direction::SouthWest, this);
		if (moveResult.BlockOccupied || !moveResult.ValidMove)
			moveResult = m_pNavigator.lock()->Move(Direction::NorthWest, this);
	}

	coilyRow = m_pNavigator.lock()->GetCurrentRow();
	coilyCol = m_pNavigator.lock()->GetCurrentColumn();
	const int distanceToTargetEnd = ExtraMath::DistanceFromTo(coilyRow, coilyCol, targetRow, targetCol);

	//Check if coily jumped of the map
	if ((!moveResult.ValidMove && m_IsMovingToTarget) || (m_IsMovingToTarget && distanceToTargetEnd > distanceToTargetStart))
	{
		ServiceLocator::GetSoundSystem()->PlayEffect("../Data/Sound/SnakeFall.wav");
		const auto score = m_pGameObject->GetScene()->FindObjectOfType<ScoreComponent>();
		if (!score.expired() && score.lock().get() != nullptr)
		{
			score.lock()->AddScore(500);
		}

		Despawn();
	}
}


MoveResult CoilyComponent::FullReset()
{
	Transform(true);
	return m_pNavigator.lock()->MoveToSquare(m_SpawnIndex, this);
}

void CoilyComponent::Despawn()
{
	m_pGameObject->MarkForDelete();
}

void CoilyComponent::Notify(EventType type, EventData*)
{
	switch (type)
	{
	case EventType::PlayerDamageTaken:
	case EventType::PlayerKilled:
	case EventType::PlayerFallen:
		Despawn();
		break;
	}
}

void CoilyComponent::DiscTriggered()
{
	if (m_pQBertNavigator.expired()) return;
	m_TargetRow = m_pQBertNavigator.lock()->GetCurrentRow();
	m_TargetColumn = m_pQBertNavigator.lock()->GetCurrentColumn();

	int distanceToTarget = ExtraMath::DistanceFromTo(m_pNavigator.lock()->GetCurrentRow()
		, m_pNavigator.lock()->GetCurrentColumn()
		, m_TargetRow, m_TargetColumn);

	if (m_HasTransformed && distanceToTarget <= m_MaxDistanceToTarget) m_IsMovingToTarget = true;
}

void CoilyComponent::Transform(bool isEgg)
{
	m_HasTransformed = !isEgg;
	if (!m_pTexture.expired())
	{
		if (isEgg)
		{
			m_pTexture.lock()->SetTexture("Enemies/coily1.png");
		}
		else
		{
			m_pTexture.lock()->SetTexture("Enemies/coily2.png");
		}
	}
}
std::weak_ptr<LevelNavigatorComponent> CoilyComponent::GetClosestQBert() const
{
	auto qbertComponents = m_pGameObject->GetScene()->FindObjectsOfType<QBertComponent>();
	
	std::weak_ptr<LevelNavigatorComponent> closestQBert;
	int closestDistance = 2000;
	for (auto qbert : qbertComponents)
	{
		auto qbertNavigator = qbert.lock()->GetGameObject()->GetComponent<LevelNavigatorComponent>();
		int distance = ExtraMath::DistanceFromTo(
			qbertNavigator.lock()->GetCurrentRow()
			, qbertNavigator.lock()->GetCurrentColumn()
			, m_pNavigator.lock()->GetCurrentRow()
			, m_pNavigator.lock()->GetCurrentColumn());

		if (distance < closestDistance)
		{
			closestQBert = qbertNavigator;
			closestDistance = distance;
		}
	}
	return closestQBert;
}
