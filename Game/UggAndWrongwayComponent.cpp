#include "MiniginPCH.h"
#include "UggAndWrongwayComponent.h"
#include "GameControllerComponent.h"
#include "LevelNavigatorComponent.h"
#include "GameTime.h"
#include "BlockComponent.h"
#include "LevelComponent.h"

UggAndWrongwayComponent::UggAndWrongwayComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
	, const std::weak_ptr<GameControllerComponent>& pGameController, int spawnIndex, bool isLeftSide)
	: EntityComponent(pGameController,EntityType::UggAndWrongway)
	, m_pNavigator{pNavigator}
	, m_SpawnIndex{spawnIndex}
	, m_IsLeftSide{isLeftSide}
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
		if (m_IsLeftSide)
		{
			moveResult = m_pNavigator.lock()->Move(Direction::NorthEast,this);
		}
		else
		{

			moveResult = m_pNavigator.lock()->Move(Direction::NorthWest, this);
		}

		if (!moveResult.validMove) Despawn();
		m_TimeUntilNextMove = m_TimeBetweenMoves;
	}
}

void UggAndWrongwayComponent::Reset()
{
	m_pNavigator.lock()->MoveToSquare(m_SpawnIndex, this);
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
