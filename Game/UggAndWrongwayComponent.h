#pragma once
#include "BaseComponent.h"
#include "Listener.h"

class LevelNavigatorComponent;
class GameControllerComponent;
class UggAndWrongwayComponent
	: public BaseComponent
	, public Listener
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	UggAndWrongwayComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
		, const std::weak_ptr<GameControllerComponent>& pGameController, int spawnIndex
		, bool isLeftSide);
	virtual ~UggAndWrongwayComponent();

	//------COPY CONSTRUCTORS------
	UggAndWrongwayComponent(const UggAndWrongwayComponent&) = delete;
	UggAndWrongwayComponent(UggAndWrongwayComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	UggAndWrongwayComponent operator=(const UggAndWrongwayComponent&) = delete;
	UggAndWrongwayComponent& operator=(UggAndWrongwayComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;
	void Reset();
	void Despawn();
	void Notify(EventType type, EventData* eventData) override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	std::weak_ptr<LevelNavigatorComponent> m_pNavigator;
	const float m_TimeBetweenMoves = 1.f;
	float m_TimeUntilNextMove;
	int m_SpawnIndex;

	bool m_IsLeftSide;
};
