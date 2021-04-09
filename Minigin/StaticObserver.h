#pragma once

#include "Singleton.h"
#include "Events.h"

class Listener;

class StaticObserver
	: public dae::Singleton<StaticObserver>
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	virtual ~StaticObserver() = default;

	//------PUBLIC FUNCTIONS------
	void Notify(EventType type, EventData* eventData = nullptr);

	void AddListener(Listener* listener);
	void RemoveListener(Listener* listener);
private:
	//------PRIVATE FUNCTIONS------
	friend class dae::Singleton<StaticObserver>;
	StaticObserver() = default;

	//------PRIVATE VARIABLES------	
	std::vector<Listener*> m_pListeners;
};

