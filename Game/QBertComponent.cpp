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
	, DWORD gamepadIndex, const std::weak_ptr<GameControllerComponent>& pGameController, int spawnIndex)
	: EntityComponent(pGameController,EntityType::QBert)
	, m_pNavigator{pNavigator}
	, m_GamepadIndex{ gamepadIndex }
	, m_SpawnIndex{spawnIndex}
{
	m_Timer = m_MoveCooldown;
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
	if (value.x > threshhold && value.y > threshhold && m_Timer < 0)
	{
		m_pNavigator.lock()->Move(Direction::NorthEast, this);
		m_Timer = m_MoveCooldown;
	}

	else if (value.x < -threshhold && value.y >threshhold && m_Timer < 0)
	{
		m_pNavigator.lock()->Move(Direction::NorthWest, this);
		m_Timer = m_MoveCooldown;
	}

	else if (value.x < -threshhold && value.y < -threshhold && m_Timer < 0)
	{
		m_pNavigator.lock()->Move(Direction::SouthWest, this);
		m_Timer = m_MoveCooldown;
	}

	else if (value.x > threshhold && value.y < -threshhold && m_Timer < 0)
	{
		m_pNavigator.lock()->Move(Direction::SouthEast, this);
		m_Timer = m_MoveCooldown;
	}
}

MoveResult QBertComponent::Reset()
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
		Reset();
		break;
	case EventType::PlayerFallen:
		Reset();
		break;
	}
}
