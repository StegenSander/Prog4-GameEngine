#pragma once
#include "BaseComponent.h"
#include "Listener.h"
#include "DataStructures.h"

class GameControllerComponent;
class EntityComponent
	:public BaseComponent
	,public Listener
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	EntityComponent(const std::weak_ptr<GameControllerComponent>& pGameController,EntityType type);
	virtual ~EntityComponent();

	//------COPY CONSTRUCTORS------
	EntityComponent(const EntityComponent&) = delete;
	EntityComponent(EntityComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	EntityComponent operator=(const EntityComponent&) = delete;
	EntityComponent& operator=(EntityComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void Update() override = 0;
	virtual void Reset() = 0;
	virtual void Despawn() {};
	virtual void Notify(EventType type, EventData* eventData) override = 0;
	EntityInfo GetInfo();

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	EntityType m_Type;
};

