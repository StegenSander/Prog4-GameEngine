#pragma once
#include "BaseComponent.h"


class PlayerUIComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	PlayerUIComponent(dae::GameObject* pPlayer1, dae::GameObject* pPlayer2);
	virtual ~PlayerUIComponent() = default;

	//------COPY CONSTRUCTORS------
	PlayerUIComponent(const PlayerUIComponent&) = delete;
	PlayerUIComponent(PlayerUIComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	PlayerUIComponent operator=(const PlayerUIComponent&) = delete;
	PlayerUIComponent& operator=(PlayerUIComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;
	void Render() override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------



	//------PRIVATE VARIABLES------	
	dae::GameObject* m_pPlayer1;
	dae::GameObject* m_pPlayer2;
};

