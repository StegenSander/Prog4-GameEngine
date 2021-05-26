#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "TextureComponent.h"
#include "GameControllerComponent.h"

HealthComponent::HealthComponent(int health,const std::weak_ptr<TextureComponent>& pTexture
	, const std::weak_ptr<GameControllerComponent>& pGameController)
	: m_InitialHealth{health}
	, m_Health{health}
	, m_pTexture{pTexture}
	, m_pGameController{pGameController}
	, Listener(pGameController)
{
}

HealthComponent::~HealthComponent()
{
	std::cout << "Health component desturctor\n";
}

void HealthComponent::Damage()
{
	m_Health--;
	UpdateTexture();
	if (m_Health <= 0)
	{
		ResetHealth();
		if (m_pGameController.expired()) return;
		m_pGameController.lock()->PlayerKilled();
	}
}

void HealthComponent::ResetHealth()
{
	m_Health = m_InitialHealth;
	UpdateTexture();
}

void HealthComponent::UpdateTexture()
{
	if (m_pTexture.expired()) return;
	if (m_Health < 1 || m_Health > 3) return;
	m_pTexture.lock()->SetTexture("Health/Health_" + std::to_string(m_Health) + ".png");
}

void HealthComponent::Notify(EventType type, EventData*)
{
	if (type == EventType::PlayerFallen || type == EventType::PlayerDamageTaken)
	{
		Damage();
	}
}
