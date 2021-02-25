#pragma once
#include "ListenerComponent.h"
class PlayerListenerComponent
	: public ListenerComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	PlayerListenerComponent();
	virtual ~PlayerListenerComponent() = default;

	//------COPY CONSTRUCTORS------
	PlayerListenerComponent(const PlayerListenerComponent&) = delete;
	PlayerListenerComponent(PlayerListenerComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	PlayerListenerComponent operator=(const PlayerListenerComponent&) = delete;
	PlayerListenerComponent& operator=(PlayerListenerComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Notify(EventType type, EventData* eventData) override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};

