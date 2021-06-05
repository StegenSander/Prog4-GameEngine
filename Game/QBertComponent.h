#pragma once
#include "EntityComponent.h"

class LevelNavigatorComponent;
class GameControllerComponent;
class QBertComponent final:
	public EntityComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	QBertComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
		, DWORD gamepadIndex, const std::weak_ptr<GameControllerComponent>& pGameController
		, int spawnIndex, float timeBetweenMoves = 0.4f);
	virtual ~QBertComponent();

	//------COPY CONSTRUCTORS------
	QBertComponent(const QBertComponent&) = delete;
	QBertComponent(QBertComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	QBertComponent operator=(const QBertComponent&) = delete;
	QBertComponent& operator=(QBertComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;
	void Move(Direction direction);
	MoveResult FullReset() override;
	void Notify(EventType type, EventData* eventData) override;

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
	float m_TimeBetweenMoves{ 0.3f };
	int m_SpawnIndex;
};

