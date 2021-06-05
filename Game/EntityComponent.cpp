#include "MiniginPCH.h"
#include "EntityComponent.h"
#include "GameControllerComponent.h"

EntityComponent::EntityComponent(const std::weak_ptr<GameControllerComponent>& pGameController, EntityType type)
	: Listener(pGameController)
	, m_Type{type}
{
}

EntityInfo EntityComponent::GetInfo()
{
	EntityInfo info;
	info.Behaviour = this;
	info.Type = m_Type;
	return info;
}
