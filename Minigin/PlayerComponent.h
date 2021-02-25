#pragma once
#include "BaseComponent.h"
class PlayerComponent
	:public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	PlayerComponent(int playerIndex);
	virtual ~PlayerComponent() = default;

	//------COPY CONSTRUCTORS------
	PlayerComponent(const PlayerComponent&) = delete;
	PlayerComponent(PlayerComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	PlayerComponent operator=(const PlayerComponent&) = delete;
	PlayerComponent& operator=(PlayerComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void ScorePoint(int amount);
	void Update() override {};

	int GetPlayerIndex() const { return m_PlayerIndex; }

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	int m_PlayerIndex;
};

