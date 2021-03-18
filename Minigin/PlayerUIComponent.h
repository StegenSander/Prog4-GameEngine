#pragma once
#include "BaseComponent.h"
#include "Listener.h"

class HealthComponent;
class ScoreComponent;

class PlayerUIComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	PlayerUIComponent(const std::weak_ptr<dae::GameObject>& pPlayer1, const std::weak_ptr<dae::GameObject>& pPlayer2);
	virtual ~PlayerUIComponent() {
		std::cout << "PlayerUI Component deleted\n";
	};

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
	std::weak_ptr<dae::GameObject> m_pPlayer1;
	std::weak_ptr<HealthComponent> m_pPlayer1Health;
	std::weak_ptr<ScoreComponent> m_pPlayer1Score;

	std::weak_ptr<dae::GameObject> m_pPlayer2;
	std::weak_ptr<HealthComponent> m_pPlayer2Health;
	std::weak_ptr<ScoreComponent> m_pPlayer2Score;
};

