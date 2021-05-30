#pragma once
#include "BaseComponent.h"
#include "Listener.h"
class TextureComponent;
class GameControllerComponent;
class HealthComponent
	: public BaseComponent
	, public Listener
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	HealthComponent(int health,const std::weak_ptr<TextureComponent>& pTexture
		,const std::weak_ptr<GameControllerComponent>& pGameController);
	virtual ~HealthComponent();

	//------COPY CONSTRUCTORS------
	HealthComponent(const HealthComponent&) = delete;
	HealthComponent(HealthComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	HealthComponent operator=(const HealthComponent&) = delete;
	HealthComponent& operator=(HealthComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Damage();
	void ResetHealth();
	void Update() override;
	void UpdateTexture();

	void Notify(EventType type, EventData* eventData) override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	std::weak_ptr<TextureComponent> m_pTexture;
	std::weak_ptr<GameControllerComponent> m_pGameController;
	int m_Health;
	int m_InitialHealth;
	float m_MinTimeBetweenDamage = 0.2f;
	float m_Timer = 0.f;
};

