#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "Observer.h"

HealthComponent::HealthComponent(int totalHealth)
	: m_CurrentHealth{totalHealth}
	, m_MaxHealth{totalHealth}
{
}

void HealthComponent::DealDamage(int amount)
{
	m_CurrentHealth -= amount;

	PlayerDamageData damageData{ m_pGameObject,m_CurrentHealth,amount };
	Observer::GetInstance().Notify(EventType::PlayerDamage, &damageData);

	if (m_CurrentHealth <= 0)
	{
		EventData eventData{ m_pGameObject };
		Observer::GetInstance().Notify(EventType::PlayerDied, &eventData);
		m_pGameObject->Delete();
		std::cout << "Deleting objects";
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
