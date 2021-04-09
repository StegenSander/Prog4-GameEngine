#pragma once
#include "Events.h"

class Listener;

class Subject
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	Subject() = default;
	virtual ~Subject() = default;

	//------PUBLIC FUNCTIONS------
	void Notify(EventType type, EventData* eventData = nullptr);

	void AddListener(Listener* listener);
	void RemoveListener(Listener* listener);
private:
	//------PRIVATE VARIABLES------	
	std::vector<Listener*> m_pListeners;
};

