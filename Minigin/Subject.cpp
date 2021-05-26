#include "MiniginPCH.h"
#include "Subject.h"
#include "Listener.h"

void Subject::Notify(EventType type, EventData* eventData)
{
	for (Listener* pListener : m_pListeners)
	{
		pListener->Notify(type, eventData);
	}
}

void Subject::AddListener(Listener* pListener)
{
	//only add if not already in the vector
	if (std::find(m_pListeners.begin(), m_pListeners.end(), pListener) == m_pListeners.end())
	{
		m_pListeners.push_back(pListener);
		std::cout << "Listener added: " << m_pListeners.size() << " Listeners active\n";
	}
}

void Subject::RemoveListener(Listener* pListener)
{
	auto vecIt = std::find(m_pListeners.begin(), m_pListeners.end(), pListener);
	if (vecIt != m_pListeners.end())
	{
		m_pListeners.erase(vecIt);
		std::cout << "Listener removed " << m_pListeners.size() << " Listeners active\n";
	}
}