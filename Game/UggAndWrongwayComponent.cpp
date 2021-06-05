#include "MiniginPCH.h"
#include "UggAndWrongwayComponent.h"
#include "GameControllerComponent.h"
#include "LevelNavigatorComponent.h"
#include "GameTime.h"
#include "BlockComponent.h"
#include "LevelComponent.h"

UggAndWrongwayComponent::UggAndWrongwayComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
	, const std::weak_ptr<GameControllerComponent>& pGameController
	, int spawnIndex, bool isLeftSide, float timeBetweenMoves)
	: EntityComponent(pGameController,EntityType::UggAndWrongway)
	, m_pNavigator{pNavigator}
	, m_SpawnIndex{spawnIndex}
	, m_IsLeftSide{isLeftSide}
	, m_TimeBetweenMoves{timeBetweenMoves}
{
	m_TimeUntilNextMove = m_TimeBetweenMoves;
}

UggAndWrongwayComponent::~UggAndWrongwayComponent()
{
}

void UggAndWrongwayComponent::Update()
{
	float deltaTime = GameTime::GetInstance().GetDeltaTime();
	m_TimeUntilNextMove -= deltaTime;
	if (m_TimeUntilNextMove < 0)
	{
		MoveResult moveResult;
		if (m_IsLeftSide) moveResult = m_pNavigator.lock()->Move(Direction::NorthEast,this);
		else moveResult = m_pNavigator.lock()->Move(Direction::NorthWest, this);

		if (moveResult.BlockOccupied)
		{
			if (m_IsLeftSide) moveResult = 
				m_pNavigator.lock()->MoveToSquare(
					m_pNavigator.lock()->GetCurrentRow(), 
					m_pNavigator.lock()->GetCurrentColumn() +1,this);
			else moveResult = 
				m_pNavigator.lock()->MoveToSquare(
				m_pNavigator.lock()->GetCurrentRow(),
				m_pNavigator.lock()->GetCurrentColumn() - 1, this);
		}

		if (!moveResult.ValidMove) Despawn();
		m_TimeUntilNextMove = m_TimeBetweenMoves;
	}
}

MoveResult UggAndWrongwayComponent::FullReset()
{
	return m_pNavigator.lock()->MoveToSquare(m_SpawnIndex, this);
}

void UggAndWrongwayComponent::Despawn()
{
	m_pGameObject->MarkForDelete();
}

void UggAndWrongwayComponent::Notify(EventType type, EventData*)
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
