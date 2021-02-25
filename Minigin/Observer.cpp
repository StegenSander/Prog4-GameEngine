#include "MiniginPCH.h"
#include "Observer.h"
#include "ListenerComponent.h"

void Observer::Notify(EventType type, EventData* eventData)
{
	for (ListenerComponent* pListener : m_pListeners)
	{
		pListener->Notify(type,eventData);
	}
}

void Observer::AddListener(ListenerComponent* pListener)
{
	//only add if not already in the vector
	if (std::find(m_pListeners.begin(),m_pListeners.end(), pListener) == m_pListeners.end())
	{
		m_pListeners.push_back(pListener);
	}
}

void Observer::RemoveListener(ListenerComponent* pListener)
{
	auto vecIt = std::find(m_pListeners.begin(), m_pListeners.end(), pListener);
	if (vecIt != m_pListeners.end())
	{
		m_pListeners.erase(vecIt);
	}
}
