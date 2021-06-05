#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "GameControllerComponent.h"

ScoreComponent::ScoreComponent(const std::weak_ptr<TextComponent>& textComp, int initialScore)
	: m_TextComp{textComp}
	, m_Score{initialScore}
{
}

ScoreComponent::~ScoreComponent()
{
}

void ScoreComponent::Update()
{
}

void ScoreComponent::AddScore(int amount)
{
	m_Score += amount;
	UpdateText();
}

int ScoreComponent::GetScore()
{
	return m_Score;
}

void ScoreComponent::ResetScore()
{
	m_Score = 0;
	UpdateText();
}

void ScoreComponent::UpdateText()
{
	if (m_TextComp.expired()) return;
	m_TextComp.lock()->SetText(std::to_string(m_Score));
}
