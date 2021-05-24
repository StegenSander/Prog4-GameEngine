#pragma once
#include <BaseComponent.h>

class LevelNavigatorComponent;
class QBertComponent:
	public BaseComponent 
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	QBertComponent(const std::weak_ptr<LevelNavigatorComponent>& navigator, DWORD gamepadIndex);
	virtual ~QBertComponent();

	//------COPY CONSTRUCTORS------
	QBertComponent(const QBertComponent&) = delete;
	QBertComponent(QBertComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	QBertComponent operator=(const QBertComponent&) = delete;
	QBertComponent& operator=(QBertComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	std::weak_ptr<LevelNavigatorComponent> m_pNavigator;
	DWORD m_GamepadIndex;
	float m_Timer;
	float m_MoveCooldown{ 0.4f };
};

