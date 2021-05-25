#pragma once
#include "BaseComponent.h"
#include "Subject.h"
class TextureComponent;
class HealthComponent
	: public BaseComponent
	, public Subject
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	HealthComponent(int health, std::weak_ptr<TextureComponent> pTexture);
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
	void Update() override {};
	void UpdateTexture();

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	std::weak_ptr<TextureComponent> m_pTexture;
	int m_Health;
	int m_InitialHealth;
};

