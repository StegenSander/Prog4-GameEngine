#pragma once
#include "Events.h"

class Listener;

class Subject
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	Subject() = default;
	virtual ~Subject() { std::cout << "Subject destructor\n"; };

	//------PUBLIC FUNCTIONS------
	void Notify(EventType type, EventData* eventData = nullptr);

	void AddListener(Listener* listener);
	void RemoveListener(Listener* listener);
private:
	//------PRIVATE VARIABLES------	
	std::vector<Listener*> m_pListeners;
};

