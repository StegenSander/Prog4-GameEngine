#pragma once
#include "EntityComponent.h"

class LevelNavigatorComponent;
class GameControllerComponent;
class TextureComponent;

class CoilyPlayerComponent
	: public EntityComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	CoilyPlayerComponent(const std::weak_ptr<LevelNavigatorComponent>& pNavigator
		, const std::weak_ptr<GameControllerComponent>& pGameController
		, const std::weak_ptr<TextureComponent>& pTexture
		, int spawnIndex, DWORD gamePadIndex, float timeBetweenMoves = 1.f);
	virtual ~CoilyPlayerComponent();

	//------COPY CONSTRUCTORS------
	CoilyPlayerComponent(const CoilyPlayerComponent&) = delete;
	CoilyPlayerComponent(CoilyPlayerComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	CoilyPlayerComponent operator=(const CoilyPlayerComponent&) = delete;
	CoilyPlayerComponent& operator=(CoilyPlayerComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;

	MoveResult FullReset() override;
	void Despawn() override;
	void Notify(EventType type, EventData* eventData) override;

	void Move(Direction direction);

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	void Transform(bool isEgg);

	//------PRIVATE VARIABLES------
	std::weak_ptr<LevelNavigatorComponent> m_pNavigator;
	std::weak_ptr<TextureComponent> m_pTexture;

	DWORD m_GamepadIndex;
	const float m_TimeBetweenMoves;
	float m_TimeUntilNextMove;
	int m_SpawnIndex;

	bool m_HasTransformed;
};
