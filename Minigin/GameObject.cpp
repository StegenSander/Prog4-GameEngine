#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"

dae::GameObject::GameObject()
	: Destroyable()
	,m_Transform {}
{
}

void dae::GameObject::Update()
{
	for (const std::shared_ptr<BaseComponent>& pComponent : m_Components)
	{
		pComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const std::shared_ptr<BaseComponent>& pComponent : m_Components)
	{
		pComponent->Render();
	}
}


void dae::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& pComponent)
{
	m_Components.push_back(pComponent);
	pComponent->m_pGameObject = this;
}

void dae::GameObject::PostUpdate()
{
	m_Components.erase(std::remove_if(m_Components.begin()
		, m_Components.end(),
		[](std::shared_ptr<BaseComponent> pComponent)
		{
			return pComponent->IsMarkedForDelete();
		}), m_Components.end());
}
