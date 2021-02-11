#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::AddComponent(BaseComponent* pComponent)
{
	m_Components.push_back(pComponent);
}

void dae::GameObject::AddRenderComponent(RenderComponent* pRenderComponent)
{
	m_RenderComponents.push_back(pRenderComponent);
}


void dae::GameObject::Update()
{
	for (BaseComponent* pComponent : m_Components)
	{
		pComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	for (RenderComponent* pRenderComponent : m_RenderComponents)
	{
		pRenderComponent->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}