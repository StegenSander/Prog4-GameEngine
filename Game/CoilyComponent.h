#pragma once
#include "EntityComponent.h"

class LevelNavigatorComponent;
class GameControllerComponent;
class TextureComponent;
class CoilyComponent
	: public EntityComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	CoilyComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
		, const std::weak_ptr<LevelNavigatorComponent>& pQBertNavigator
		, const std::weak_ptr<GameControllerComponent>& pGameController
		, const std::weak_ptr<TextureComponent>& pTexture
		, int spawnIndex, float timeBetweenMoves = 1.f);
	virtual ~CoilyComponent();

	//------COPY CONSTRUCTORS------
	CoilyComponent(const CoilyComponent&) = delete;
	CoilyComponent(CoilyComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	CoilyComponent operator=(const CoilyComponent&) = delete;
	CoilyComponent& operator=(CoilyComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;

	MoveResult Reset() override;
	void Despawn() override;
	void Notify(EventType type, EventData* eventData) override;

	void DiscTriggered();

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	void Transform(bool isEgg);

	//------PRIVATE VARIABLES------	
	std::weak_ptr<LevelNavigatorComponent> m_pNavigator;
	std::weak_ptr<LevelNavigatorComponent> m_pQBertNavigator;
	std::weak_ptr<TextureComponent> m_pTexture;
	const float m_TimeBetweenMoves;
	float m_TimeUntilNextMove;
	int m_SpawnIndex;

	//Move To Target Data
	int m_MaxDistanceToTarget = 3;
	int m_TargetRow;
	int m_TargetColumn;
	bool m_IsMovingToTarget;

	bool m_HasTransformed;
};

