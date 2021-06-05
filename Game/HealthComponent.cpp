#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "TextureComponent.h"
#include "GameControllerComponent.h"
#include "GameTime.h"

HealthComponent::HealthComponent(int initialHealth, int maxHealth,const std::weak_ptr<TextureComponent>& pTexture
	, const std::weak_ptr<GameControllerComponent>& pGameController)
	: m_MaxHealth{ maxHealth }
	, m_Health{ initialHealth }
	, m_pTexture{pTexture}
	, m_pGameController{pGameController}
	, Listener(pGameController)
{
	UpdateTexture();
}

HealthComponent::~HealthComponent()
{
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
void HealthComponent::Update()
{
	m_Timer -= GameTime::GetInstance().GetDeltaTime();
}
void HealthComponent::ResetHealth()
{
	m_Health = m_MaxHealth;
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
		if (m_Timer < 0.f)
		{
			Damage();
			m_Timer = m_MinTimeBetweenDamage;
		}
	}
}
