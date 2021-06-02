#pragma once
#include "EntityComponent.h"

class LevelNavigatorComponent;
class GameControllerComponent;
class SlickAndSamComponent final
	: public EntityComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	SlickAndSamComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
		,const std::weak_ptr<GameControllerComponent>& pGameController
		, int spawnIndex, float timeBetweenMoves =0.5f);
	virtual ~SlickAndSamComponent();

	//------COPY CONSTRUCTORS------
	SlickAndSamComponent(const SlickAndSamComponent&) = delete;
	SlickAndSamComponent(SlickAndSamComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	SlickAndSamComponent operator=(const SlickAndSamComponent&) = delete;
	SlickAndSamComponent& operator=(SlickAndSamComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;

	MoveResult Reset() override;
	void Despawn() override;
	void Notify(EventType type, EventData* eventData) override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	std::weak_ptr<LevelNavigatorComponent> m_pNavigator;
	const float m_TimeBetweenMoves = 0.5f;
	float m_TimeUntilNextMove;
	int m_SpawnIndex;
};

