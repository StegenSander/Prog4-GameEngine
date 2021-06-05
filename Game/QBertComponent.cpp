#include "MiniginPCH.h"
#include "QBertComponent.h"
#include "InputManager.h"
#include "Scene.h"
#include "GameTime.h"
#include "LevelNavigatorComponent.h"
#include "HealthComponent.h"
#include "GameControllerComponent.h"
#include "LevelComponent.h"


QBertComponent::QBertComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
	, DWORD gamepadIndex, const std::weak_ptr<GameControllerComponent>& pGameController
	, int spawnIndex, float timeBetweenMoves)
	: EntityComponent(pGameController,EntityType::QBert)
	, m_pNavigator{pNavigator}
	, m_GamepadIndex{ gamepadIndex }
	, m_SpawnIndex{spawnIndex}
	, m_TimeBetweenMoves{timeBetweenMoves}
{
	m_Timer = m_TimeBetweenMoves;
}

QBertComponent::~QBertComponent()
{
}

void QBertComponent::Update()
{
	m_pNavigator.lock()->UnRegisterFromBlock();
	m_pNavigator.lock()->RegisterOnBlock(this);

	auto sceneData = m_pGameObject->GetScene()->GetSceneData();
	JoystickValue value = sceneData->pInputManager->GetJoystickValue(m_GamepadIndex, true);

	m_Timer -= GameTime::GetInstance().GetDeltaTime();
	
	const float threshhold = 0.3f;
	if (value.x > threshhold && value.y > threshhold)
	{
		Move(Direction::NorthEast);
	}

	else if (value.x < -threshhold && value.y >threshhold)
	{
		Move(Direction::NorthWest);
	}

	else if (value.x < -threshhold && value.y < -threshhold)
	{
		Move(Direction::SouthWest);
	}

	else if (value.x > threshhold && value.y < -threshhold)
	{
		Move(Direction::SouthEast);
	}
}

void QBertComponent::Move(Direction direction)
{
	if (m_Timer <0)
	{
		m_pNavigator.lock()->Move(direction, this);
		m_Timer = m_TimeBetweenMoves;
	}
}

MoveResult QBertComponent::FullReset()
{
	return m_pNavigator.lock()->MoveToSquare(m_SpawnIndex,this);
}

void QBertComponent::Notify(EventType type, EventData*)
{
	switch (type)
	{
	case EventType::PlayerDamageTaken:
		break;
	case EventType::PlayerKilled:
		FullReset();
		break;
	case EventType::PlayerFallen:
		FullReset();
		break;
	}
}
