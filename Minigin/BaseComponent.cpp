#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

BaseComponent::BaseComponent(dae::GameObject* pGameObject)
	: m_pGameObject(pGameObject)
{

}

void BaseComponent::PushComponentToGameObject()
{
	m_pGameObject->AddComponent(this);
}
