#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "GameObject.h"

RenderComponent::RenderComponent(dae::GameObject* pGameObject)
	:BaseComponent(pGameObject)
{
}

void RenderComponent::PushRenderComponentToGameObject()
{
	m_pGameObject->AddRenderComponent(this);
}
