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
	

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	friend class dae::Singleton<StaticObserver>;
	StaticObserver() = default;

	//------PRIVATE VARIABLES------	
	std::vector<Listener*> m_pListeners;
};

