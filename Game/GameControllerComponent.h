#pragma once
#include <BaseComponent.h>
#include "Subject.h"

class GameControllerComponent
	: public BaseComponent
	, public Subject
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	GameControllerComponent();
	virtual ~GameControllerComponent();

	//------COPY CONSTRUCTORS------
	GameControllerComponent(const GameControllerComponent&) = delete;
	GameControllerComponent(GameControllerComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	GameControllerComponent operator=(const GameControllerComponent&) = delete;
	GameControllerComponent& operator=(GameControllerComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void PlayerKilled();
	void PlayerDamaged();
	void PlayerOffMap();

	void Update() override {};

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};

