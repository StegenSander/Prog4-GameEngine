#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "StaticObserver.h"
#include "InputManager.h"

ScoreComponent::ScoreComponent()
    :BaseComponent()
    ,m_Score{0}
{
}

int ScoreComponent::ScorePoint(int amount)
{
    std::cout << "Scored" << amount << std::endl;
    m_Score += amount;
    ScorePointData scoreData{ m_pGameObject,amount,m_Score };
    StaticObserver::GetInstance().Notify(EventType::ScorePoint, &scoreData);
    return m_Score;
}

int ScoreComponent::GetScore() const
{
    return m_Score;
}
