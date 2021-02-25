#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "InputManager.h"
#include "Observer.h"

PlayerComponent::PlayerComponent(int playerIndex)
	:BaseComponent()
	,m_PlayerIndex(playerIndex)
{
	dae::InputManager::GetInstance().AddCommand(ControllerButtonData{ ControllerButton::ButtonB,ButtonState::OnRelease }
	, new Command{ std::bind(&PlayerComponent::ScorePoint,this,10) }, playerIndex);
	dae::InputManager::GetInstance().AddCommand(ControllerButtonData{ ControllerButton::ButtonX,ButtonState::OnRelease }
	, new Command{ std::bind(&PlayerComponent::ScorePoint,this,50) }, playerIndex);
	dae::InputManager::GetInstance().AddCommand(ControllerButtonData{ ControllerButton::ButtonY,ButtonState::OnRelease }
	, new Command{ std::bind(&PlayerComponent::ScorePoint,this,100) }, playerIndex);
}

void PlayerComponent::ScorePoint(int amount)
{
	ScorePointData scoreData{ m_pGameObject,amount };
	Observer::GetInstance().Notify(EventType::ScorePoint, &scoreData);
}
