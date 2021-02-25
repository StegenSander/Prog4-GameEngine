#include "MiniginPCH.h"
#include "PlayerUIComponent.h"
#include "imgui.h"

#include "HealthComponent.h"
#include "PlayerComponent.h"
#include "ScoreboardComponent.h"

PlayerUIComponent::PlayerUIComponent(dae::GameObject* pPlayer1, dae::GameObject* pPlayer2)
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
	ImGui::Begin("Player1");

	std::string score{ "Score: " + std::to_string(m_pPlayer1->GetComponent<ScoreboardComponent>().lock()->GetScore()) };
	ImGui::Text(score.c_str());

	std::string health{ "Health: " + std::to_string(m_pPlayer1->GetComponent<HealthComponent>().lock()->GetHealth()) };
	ImGui::Text(health.c_str());

	ImGui::End();

	ImGui::Begin("Player2");

	score={ "Score: " + std::to_string(m_pPlayer2->GetComponent<ScoreboardComponent>().lock()->GetScore()) };
	ImGui::Text(score.c_str());

	health= { "Health: " + std::to_string(m_pPlayer2->GetComponent<HealthComponent>().lock()->GetHealth()) };
	ImGui::Text(health.c_str());

	ImGui::End();
	
}
