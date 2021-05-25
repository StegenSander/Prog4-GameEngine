#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "HealthEvents.h"

HealthComponent::HealthComponent(int health)
	: m_InitialHealth{health}
	, m_Health{health}
	, Subject()
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Damage()
{
	m_Health--;
	if (m_Health <= 0)
	{
		Notify(EventType::PlayerKilled);
		ResetHealth();
	}
	else
	{
		DamageTakenEvent event{};
		event.Sender = this;
		event.healthRemaining = m_Health;
		Notify(EventType::PlayerDamageTaken, &event);
	}
}

void HealthComponent::ResetHealth()
{
	m_Health = m_InitialHealth;
}
