#include "MiniginPCH.h"
#include "CoilyComponent.h"
#include "GameControllerComponent.h"
#include "LevelNavigatorComponent.h"
#include "GameTime.h"
#include "BlockComponent.h"
#include "TextureComponent.h"
#include "LevelComponent.h"
#include "ExtraMath.h"


CoilyComponent::CoilyComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
	, const std::weak_ptr<LevelNavigatorComponent>& pQBertNavigator
	, const std::weak_ptr<GameControllerComponent>& pGameController
	, const std::weak_ptr<TextureComponent>& pTexture
	, int spawnIndex, float timeBetweenMoves)
	: EntityComponent(pGameController,EntityType::Coily)
	, m_SpawnIndex(spawnIndex)
	, m_pNavigator{pNavigator}
	, m_pQBertNavigator{pQBertNavigator}
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
			bool moveLeft = bool(rand() % 2); //is 0 or 1

			MoveResult moveResult;
			if (moveLeft) moveResult = m_pNavigator.lock()->Move(Direction::SouthWest,this);
			else moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);

			if (moveResult.BlockOccupied)
			{
				moveLeft = !moveLeft;
				if (moveLeft) moveResult = m_pNavigator.lock()->Move(Direction::SouthWest, this);
				else moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);
			}

			if (!moveResult.ValidMove) Transform(false);
		}
		else //Coily movement (chase player)
		{
			if (!m_pQBertNavigator.expired())
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
				int distanceToTargetStart = ExtraMath::DistanceFromTo(coilyRow, coilyCol, targetRow, targetCol);


				int rowDif = targetRow - coilyRow;
				int colDif = targetCol - coilyCol;
				if (abs(rowDif) + abs(colDif) == 0 && m_IsMovingToTarget) m_IsMovingToTarget = false;

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
					moveResult  = m_pNavigator.lock()->Move(Direction::NorthEast, this);
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
					moveResult =  m_pNavigator.lock()->Move(Direction::SouthWest, this);
					if (moveResult.BlockOccupied || !moveResult.ValidMove)
						moveResult = m_pNavigator.lock()->Move(Direction::NorthWest, this);
				}

				coilyRow = m_pNavigator.lock()->GetCurrentRow();
				coilyCol = m_pNavigator.lock()->GetCurrentColumn();
				int distanceToTargetEnd = ExtraMath::DistanceFromTo(coilyRow, coilyCol, targetRow, targetCol);

				if ((!moveResult.ValidMove && m_IsMovingToTarget) || (m_IsMovingToTarget && distanceToTargetEnd > distanceToTargetStart))
				{
					Despawn();
				}
			}
		}

		m_TimeUntilNextMove = m_TimeBetweenMoves;
	}
}

MoveResult CoilyComponent::Reset()
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
