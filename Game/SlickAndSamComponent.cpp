#include "MiniginPCH.h"
#include "SlickAndSamComponent.h"
#include "GameControllerComponent.h"
#include "LevelNavigatorComponent.h"
#include "GameTime.h"
#include "BlockComponent.h"

SlickAndSamComponent::SlickAndSamComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
	, const std::weak_ptr<GameControllerComponent>& pGameController, int spawnIndex)
	: Listener(pGameController)
	, m_pNavigator(pNavigator)
	, m_SpawnIndex{spawnIndex}
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

		BlockComponent* moveResult;
		//If statement can be removed with some bit magic
		if (moveLeft)
		{
			moveResult =m_pNavigator.lock()->Move(Direction::SouthWest);
		}
		else
		{
			moveResult =m_pNavigator.lock()->Move(Direction::SouthEast);
		}

		//Despawn if they did an invalid move (when they are at the bottom of the triangle)
		if (!moveResult) Despawn();

		m_TimeUntilNextMove = m_TimeBetweenMoves;
	}
}

void SlickAndSamComponent::Reset()
{
	m_pNavigator.lock()->MoveToSquare(m_SpawnIndex);
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