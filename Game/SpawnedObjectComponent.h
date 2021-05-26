#pragma once
#include <BaseComponent.h>

class SpawnerComponent;
class SpawnedObjectComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	SpawnedObjectComponent(SpawnerComponent* owner);
	virtual ~SpawnedObjectComponent();

	//------COPY CONSTRUCTORS------
	SpawnedObjectComponent(const SpawnedObjectComponent&) = delete;
	SpawnedObjectComponent(SpawnedObjectComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	SpawnedObjectComponent operator=(const SpawnedObjectComponent&) = delete;
	SpawnedObjectComponent& operator=(SpawnedObjectComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() {};

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	SpawnerComponent* m_Owner;
};

