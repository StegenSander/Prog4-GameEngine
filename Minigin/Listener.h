#pragma once
#include "Events.h"

class Listener
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	Listener();
	virtual ~Listener();

	//------COPY CONSTRUCTORS------
	Listener(const Listener&) = delete;
	Listener(Listener&&) = delete;
	//------ASSIGNMENT OPERATORS------
	Listener operator=(const Listener&) = delete;
	Listener& operator=(Listener&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void Notify(EventType type, EventData* eventData) = 0;
};

