#include "MiniginPCH.h"
#include "QBertComponent.h"
#include "InputManager.h"
#include "Scene.h"
#include "GameTime.h"
#include "LevelNavigatorComponent.h"


QBertComponent::QBertComponent(const std::weak_ptr<LevelNavigatorComponent>& navigator, DWORD gamepadIndex)
	: m_GamepadIndex{gamepadIndex}
	, m_pNavigator{navigator}
{
	m_Timer = m_MoveCooldown;
}

QBertComponent::~QBertComponent()
{
}

void QBertComponent::Update()
{
	auto sceneData = m_pGameObject->GetScene()->GetSceneData();
	JoystickValue value = sceneData->pInputManager->GetJoystickValue(m_GamepadIndex, true);

	m_Timer -= GameTime::GetInstance().GetDeltaTime();
	
	const float threshhold = 0.3f;
	if (value.x > threshhold && value.y > threshhold && m_Timer < 0)
	{
		m_pNavigator.lock()->Move(Direction::NorthEast);
		m_Timer = m_MoveCooldown;
	}

	if (value.x < -threshhold && value.y >threshhold && m_Timer < 0)
	{
		m_pNavigator.lock()->Move(Direction::NorthWest);
		m_Timer = m_MoveCooldown;
	}

	if (value.x < -threshhold && value.y < -threshhold && m_Timer < 0)
	{
		m_pNavigator.lock()->Move(Direction::SouthWest);
		m_Timer = m_MoveCooldown;
	}

	if (value.x > threshhold && value.y < -threshhold && m_Timer < 0)
	{
		m_pNavigator.lock()->Move(Direction::SouthEast);
		m_Timer = m_MoveCooldown;
	}


}
