#include "MiniginPCH.h"
#include "PlayerUIComponent.h"
#include "imgui.h"

#include "HealthComponent.h"
#include "PlayerComponent.h"
#include "ScoreboardComponent.h"

PlayerUIComponent::PlayerUIComponent(const std::weak_ptr<dae::GameObject>& pPlayer1, const std::weak_ptr<dae::GameObject>& pPlayer2)
	:BaseComponent()
	,m_pPlayer1{pPlayer1}
	,m_pPlayer2{pPlayer2}

{
}

void PlayerUIComponent::Update()
{
}

void PlayerUIComponent::Render()
{
	if (!m_pPlayer1.expired())
	{
		ImGui::Begin("Player1");

		std::string score{ "Score: " + std::to_string(m_pPlayer1.lock()->GetComponent<ScoreboardComponent>().lock()->GetScore()) };
		ImGui::Text(score.c_str());

		std::string health{ "Health: " + std::to_string(m_pPlayer1.lock()->GetComponent<HealthComponent>().lock()->GetHealth()) };
		ImGui::Text(health.c_str());

		ImGui::End();
	}

	if (!m_pPlayer2.expired())
	{
		ImGui::Begin("Player2");

		std::string score = { "Score: " + std::to_string(m_pPlayer2.lock()->GetComponent<ScoreboardComponent>().lock()->GetScore()) };
		ImGui::Text(score.c_str());

		std::string health = { "Health: " + std::to_string(m_pPlayer2.lock()->GetComponent<HealthComponent>().lock()->GetHealth()) };
		ImGui::Text(health.c_str());

		ImGui::End();
	}
	
}
