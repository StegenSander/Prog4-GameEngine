#pragma once
#include "BaseComponent.h"
#include "Observer.h"

class ListenerComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	ListenerComponent();
	virtual ~ListenerComponent();

	//------COPY CONSTRUCTORS------
	ListenerComponent(const ListenerComponent&) = delete;
	ListenerComponent(ListenerComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	ListenerComponent operator=(const ListenerComponent&) = delete;
	ListenerComponent& operator=(ListenerComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void Notify(EventType type, EventData* eventData) = 0;
	virtual void Update() override {};

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};

