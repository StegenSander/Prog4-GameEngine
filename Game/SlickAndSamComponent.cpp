#include "MiniginPCH.h"
#include "SlickAndSamComponent.h"
#include "GameControllerComponent.h"
#include "LevelNavigatorComponent.h"
#include "GameTime.h"
#include "BlockComponent.h"
#include "LevelComponent.h"

SlickAndSamComponent::SlickAndSamComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
	, const std::weak_ptr<GameControllerComponent>& pGameController
	, int spawnIndex, float timeBetweenMoves)
	: EntityComponent(pGameController,EntityType::SlickAndSam)
	, m_pNavigator(pNavigator)
	, m_SpawnIndex{spawnIndex}
	, m_TimeBetweenMoves{timeBetweenMoves}
{
	m_TimeUntilNextMove = m_TimeBetweenMoves;
}

SlickAndSamComponent::~SlickAndSamComponent()
{
}

void SlickAndSamComponent::Update()
{
	float deltaTime = GameTime::GetInstance().GetDeltaTime();
	m_TimeUntilNextMove -= deltaTime;
	if (m_TimeUntilNextMove < 0)
	{
		bool moveLeft = bool(rand() % 2); //is 0 or 1

		MoveResult moveResult;
		//If statement can be removed with some bit magic
		if (moveLeft) moveResult =m_pNavigator.lock()->Move(Direction::SouthWest, this);
		else moveResult =m_pNavigator.lock()->Move(Direction::SouthEast, this);

		if (moveResult.BlockOccupied)
		{
			moveLeft = !moveLeft;
			if (moveLeft) moveResult = m_pNavigator.lock()->Move(Direction::SouthWest, this);
			else moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);
		}
		//Despawn if they did an invalid move (when they are at the bottom of the triangle)
		if (!moveResult.ValidMove)
		{
			Despawn();
			return;
		}

		m_TimeUntilNextMove = m_TimeBetweenMoves;
	}
}

MoveResult SlickAndSamComponent::Reset()
{
	return m_pNavigator.lock()->MoveToSquare(m_SpawnIndex, this);
}

void SlickAndSamComponent::Despawn()
{
	m_pGameObject->MarkForDelete();
}

void SlickAndSamComponent::Notify(EventType type, EventData*)
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
