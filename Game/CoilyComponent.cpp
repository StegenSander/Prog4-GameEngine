#include "MiniginPCH.h"
#include "CoilyComponent.h"
#include "GameControllerComponent.h"
#include "LevelNavigatorComponent.h"
#include "GameTime.h"
#include "BlockComponent.h"
#include "TextureComponent.h"
#include "LevelComponent.h"


CoilyComponent::CoilyComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
	, const std::weak_ptr<LevelNavigatorComponent>& pQBertNavigator
	, const std::weak_ptr<GameControllerComponent>& pGameController
	, const std::weak_ptr<TextureComponent>& pTexture
	, int spawnIndex)
	: EntityComponent(pGameController,EntityType::Coily)
	, m_SpawnIndex(spawnIndex)
	, m_pNavigator{pNavigator}
	, m_pQBertNavigator{pQBertNavigator}
	, m_pTexture{pTexture}
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

			if (moveResult.blockOccupied)
			{
				moveLeft = !moveLeft;
				if (moveLeft) moveResult = m_pNavigator.lock()->Move(Direction::SouthWest, this);
				else moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);
			}

			if (!moveResult.validMove) Transform(false);
		}
		else //Coily movement (chase player)
		{
			if (!m_pQBertNavigator.expired())
			{
				int qbertRow = m_pQBertNavigator.lock()->GetCurrentRow();
				int qbertCol = m_pQBertNavigator.lock()->GetCurrentColumn();

				int coilyRow = m_pNavigator.lock()->GetCurrentRow();
				int coilyCol = m_pNavigator.lock()->GetCurrentColumn();

				int rowDif = qbertRow - coilyRow;
				int colDif = qbertCol - coilyCol;

				MoveResult moveResult;
				if (colDif == 0 && rowDif < 0) m_pNavigator.lock()->Move(Direction::NorthEast, this);
				if (colDif == 0 && rowDif > 0) m_pNavigator.lock()->Move(Direction::SouthWest, this);
				if (rowDif <= 0 && colDif > 0)
				{
					moveResult  = m_pNavigator.lock()->Move(Direction::NorthEast, this);
					if (moveResult.blockOccupied) m_pNavigator.lock()->Move(Direction::SouthEast, this);
				}
				if (rowDif <= 0 && colDif < 0)
				{
					moveResult = m_pNavigator.lock()->Move(Direction::NorthWest, this);
					if (moveResult.blockOccupied) m_pNavigator.lock()->Move(Direction::NorthEast, this);
				}
				if (rowDif > 0 && colDif > 0)  
				{
					moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);
					if (moveResult.blockOccupied)m_pNavigator.lock()->Move(Direction::SouthWest, this);
				}
				if (rowDif > 0 && colDif < 0)
				{
					moveResult =  m_pNavigator.lock()->Move(Direction::SouthWest, this);
					if (moveResult.blockOccupied) m_pNavigator.lock()->Move(Direction::NorthWest, this);
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
