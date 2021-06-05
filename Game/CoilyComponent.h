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

	MoveResult FullReset() override;
	void Despawn() override;
	void Notify(EventType type, EventData* eventData) override;

	void DiscTriggered();

	//------PUBLIC VARIABLES------
private:
	//------PRIVATE FUNCTIONS------
	void Transform(bool isEgg);
	void EggMove();
	void CoilyMove();
	std::weak_ptr<LevelNavigatorComponent> GetClosestQBert() const;

	//------PRIVATE VARIABLES------	
	std::weak_ptr<LevelNavigatorComponent> m_pNavigator;
	std::weak_ptr<LevelNavigatorComponent> m_pQBertNavigator;
	std::weak_ptr<TextureComponent> m_pTexture;
	const float m_TimeBetweenMoves;
	float m_TimeUntilNextMove;
	int m_SpawnIndex;

	//Move To Target Data
	int m_MaxDistanceToTarget = 3;
	int m_TargetRow = 1;
	int m_TargetColumn = 1;
	bool m_IsMovingToTarget = false;

	bool m_HasTransformed;
};

