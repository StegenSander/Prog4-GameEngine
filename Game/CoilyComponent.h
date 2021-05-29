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
		, int spawnIndex);
	virtual ~CoilyComponent();

	//------COPY CONSTRUCTORS------
	CoilyComponent(const CoilyComponent&) = delete;
	CoilyComponent(CoilyComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	CoilyComponent operator=(const CoilyComponent&) = delete;
	CoilyComponent& operator=(CoilyComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;

	void Reset() override;
	void Despawn() override;
	void Notify(EventType type, EventData* eventData) override;

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
	const float m_TimeBetweenMoves = 1.f;
	float m_TimeUntilNextMove;
	int m_SpawnIndex;
	bool m_HasTransformed;
};

