#include "MiniginPCH.h"
#include "PlayerUIComponent.h"
#include "imgui.h"

#include "PlayerComponent.h"

PlayerUIComponent::PlayerUIComponent(const std::weak_ptr<dae::GameObject>& pPlayer1, const std::weak_ptr<dae::GameObject>& pPlayer2)
	:BaseComponent()
	,m_pPlayer1{pPlayer1}
	,m_pPlayer2{pPlayer2}

{
	/*m_pPlayer1Health = m_pPlayer1.lock()->GetComponent<HealthComponent>();
	m_pPlayer1Score = m_pPlayer1.lock()->GetComponent<ScoreComponent>();
	m_pPlayer2Health = m_pPlayer2.lock()->GetComponent<HealthComponent>();
	m_pPlayer2Score = m_pPlayer2.lock()->GetComponent<ScoreComponent>();*/
}

void PlayerUIComponent::Update()
{

}

void PlayerUIComponent::Render()
{
	if (!m_pPlayer1.expired())
	{
		/*ImGui::Begin("Player1 Data");
	
		std::string health{ "Health: " + std::to_string(m_pPlayer1Health.lock()->GetHealth())};
		ImGui::Text(health.c_str());
		ImGui::NewLine();
		std::string score{ "Score: " + std::to_string(m_pPlayer1Score.lock()->GetScore())};
		ImGui::Text(score.c_str());
		ImGui::NewLine();
		ImGui::End();*/
	}

	if (!m_pPlayer2.expired())
	{
		/*ImGui::Begin("Player2 Data");
		std::string health{ "Health: " + std::to_string(m_pPlayer2Health.lock()->GetHealth()) };
		ImGui::Text(health.c_str());
		ImGui::NewLine();
		std::string score{ "Score: " + std::to_string(m_pPlayer2Score.lock()->GetScore()) };
		ImGui::Text(score.c_str());
		ImGui::NewLine();
		ImGui::End();*/
	}
	
}
