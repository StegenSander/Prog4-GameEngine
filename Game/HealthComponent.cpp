#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "HealthEvents.h"
#include "TextureComponent.h"

HealthComponent::HealthComponent(int health, std::weak_ptr<TextureComponent> pTexture)
	: m_InitialHealth{health}
	, m_Health{health}
	, Subject()
	, m_pTexture{pTexture}
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
	UpdateTexture();
}

void HealthComponent::ResetHealth()
{
	m_Health = m_InitialHealth;
	UpdateTexture();
}

void HealthComponent::UpdateTexture()
{
	if (m_pTexture.expired()) return;
	if (m_Health < 1 && m_Health > 3) return;
	m_pTexture.lock()->SetTexture("Health/Health_" + std::to_string(m_Health) + ".png");
}
