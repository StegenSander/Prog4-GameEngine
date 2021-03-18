#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "InputManager.h"
#include "StaticObserver.h"

PlayerComponent::PlayerComponent(int playerIndex)
	:BaseComponent()
	,m_PlayerIndex(playerIndex)
{
}
