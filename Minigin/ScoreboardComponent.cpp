#include "MiniginPCH.h"
#include "ScoreboardComponent.h"

ScoreboardComponent::ScoreboardComponent()
	: ListenerComponent()
{
}

void ScoreboardComponent::Notify(EventType type, EventData* eventData)
{
	if (type == EventType::ScorePoint)
	{
		if (eventData->Sender == m_pGameObject)
		{
			ScorePointData* scoreData = static_cast<ScorePointData*>(eventData);
			m_Score += scoreData->PointsScore;
			std::cout << "Player1 Score: " << m_Score << std::endl;
		}
	}
}
