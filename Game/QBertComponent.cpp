#include "MiniginPCH.h"
#include "QBertComponent.h"
#include "InputManager.h"
#include "Scene.h"
#include "GameTime.h"
#include "LevelNavigatorComponent.h"
#include "HealthComponent.h"
#include "GameControllerComponent.h"
#include "LevelComponent.h"

#include "ServiceLocator.h"
#include "SDLSoundSystem.h"


QBertComponent::QBertComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
	, DWORD gamepadIndex, const std::weak_ptr<GameControllerComponent>& pGameController
	, int spawnIndex, float timeBetweenMoves)
	: EntityComponent(pGameController,EntityType::QBert)
	, m_pNavigator{pNavigator}
	, m_GamepadIndex{ gamepadIndex }
	, m_TimeBetweenMoves{timeBetweenMoves}
	, m_SpawnIndex{spawnIndex}
{
	m_Timer = m_TimeBetweenMoves;
}


void QBertComponent::Update()
{
	m_pNavigator.lock()->UnRegisterFromBlock();
	m_pNavigator.lock()->RegisterOnBlock(this);

	auto sceneData = m_pGameObject->GetScene()->GetSceneData();
	const JoystickValue value = sceneData->pInputManager->GetJoystickValue(m_GamepadIndex, true);

	m_Timer -= GameTime::GetInstance().GetDeltaTime();
	
	const float threshold = 0.3f;
	if (value.x > threshold && value.y > threshold)
	{
		Move(Direction::NorthEast);
	}

	else if (value.x < -threshold && value.y >threshold)
	{
		Move(Direction::NorthWest);
	}

	else if (value.x < -threshold && value.y < -threshold)
	{
		Move(Direction::SouthWest);
	}

	else if (value.x > threshold && value.y < -threshold)
	{
		Move(Direction::SouthEast);
	}
}

void QBertComponent::Move(Direction direction)
{
	if (m_Timer <0)
	{
		m_pNavigator.lock()->Move(direction, this);
		ServiceLocator::GetSoundSystem()->PlayEffect("../Data/Sound/Jump.wav");
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
		ServiceLocator::GetSoundSystem()->PlayEffect("../Data/Sound/Swear.wav");
		break;
	case EventType::PlayerKilled:
		FullReset();
		break;
	case EventType::PlayerFallen:
		ServiceLocator::GetSoundSystem()->PlayEffect("../Data/Sound/Fall.wav");
		FullReset();
		break;
	}
}
