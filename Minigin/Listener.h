#pragma once
#include "Events.h"

class Subject;
class Listener
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	Listener(const std::weak_ptr<Subject>& subject);
	virtual ~Listener();

	//------COPY CONSTRUCTORS------
	Listener(const Listener&) = delete;
	Listener(Listener&&) = delete;
	//------ASSIGNMENT OPERATORS------
	Listener& operator=(const Listener&) = delete;
	Listener& operator=(Listener&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void Notify(EventType type, EventData* eventData) = 0;
private:
	std::weak_ptr<Subject> m_Subject;
};

