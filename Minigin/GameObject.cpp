#include "MiniginPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "imgui.h"

dae::GameObject::~GameObject()
{
	for (BaseComponent* pComponent : m_Components)
	{
		delete pComponent;
	}
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


void dae::GameObject::AddComponent(BaseComponent* pComponent)
{
	m_Components.push_back(pComponent);
	pComponent->m_pGameObject = this;
	std::cout << "Component added\n";
	
	RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*> (pComponent);
	if (pRenderComponent)
	{
		m_RenderComponents.push_back(pRenderComponent);
		std::cout << "\t-> Render Component\n";
	}
}

void dae::GameObject::RemoveComponents()
{
	m_RenderComponents.erase(std::remove_if(m_RenderComponents.begin()
		, m_RenderComponents.end(),
		[](RenderComponent* pComponent)
		{
			return pComponent->IsMarkedForDelete();
		}), m_RenderComponents.end());

	m_Components.erase(std::remove_if(m_Components.begin()
		, m_Components.end(),
		[](BaseComponent* pComponent)
		{
			bool mustDelete = pComponent->IsMarkedForDelete();
			if (mustDelete) delete pComponent;
			return mustDelete;
		}), m_Components.end());
}
