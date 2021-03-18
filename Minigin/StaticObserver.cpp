#include "MiniginPCH.h"
#include "StaticObserver.h"
#include "Listener.h"


void StaticObserver::Notify(EventType type, EventData* eventData)
{
	for (Listener* pListener : m_pListeners)
	{
		pListener->Notify(type,eventData);
	}
}

void StaticObserver::AddListener(Listener* pListener)
{
	//only add if not already in the vector
	if (std::find(m_pListeners.begin(),m_pListeners.end(), pListener) == m_pListeners.end())
	{
		m_pListeners.push_back(pListener);
	}
}

void StaticObserver::RemoveListener(Listener* pListener)
{
	auto vecIt = std::find(m_pListeners.begin(), m_pListeners.end(), pListener);
	if (vecIt != m_pListeners.end())
	{
		m_pListeners.erase(vecIt);
	}
}
