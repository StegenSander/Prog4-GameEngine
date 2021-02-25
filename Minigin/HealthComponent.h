#pragma once
#include "BaseComponent.h"
class HealthComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	HealthComponent(int totalHealth);
	virtual ~HealthComponent() = default;

	//------COPY CONSTRUCTORS------
	HealthComponent(const HealthComponent&) = delete;
	HealthComponent(HealthComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	HealthComponent operator=(const HealthComponent&) = delete;
	HealthComponent& operator=(HealthComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override {};

	void DealDamage(int amount);
	void Heal(int amount);
	void SetHealth(int amount);

	int GetHealth() const {return m_CurrentHealth; }

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	int m_CurrentHealth;
	int m_MaxHealth;
};

