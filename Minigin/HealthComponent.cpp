#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "StaticObserver.h"
#include "InputManager.h"

HealthComponent::HealthComponent(int totalHealth)
	: m_CurrentHealth{totalHealth}
	, m_MaxHealth{totalHealth}
{
}

void HealthComponent::DealDamage(int amount)
{
	m_CurrentHealth -= amount;
	//std::cout << "called\n";
	PlayerDamageData damageData{ m_pGameObject,m_CurrentHealth,amount };
	StaticObserver::GetInstance().Notify(EventType::PlayerDamage, &damageData);

	if (m_CurrentHealth <= 0)
	{
		EventData eventData{ m_pGameObject };
		StaticObserver::GetInstance().Notify(EventType::PlayerDied, &eventData);

		dae::InputManager::GetInstance().MarkForDeleteByIdentifier(m_pGameObject);
		m_pGameObject->Delete();
	}
}

void HealthComponent::Heal(int amount)
{
	m_CurrentHealth += amount;
	if (m_CurrentHealth > m_MaxHealth) m_CurrentHealth = m_MaxHealth;
}

void HealthComponent::SetHealth(int amount)
{
	m_CurrentHealth = amount;
}
