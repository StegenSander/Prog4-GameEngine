#pragma once
#include <functional>
#include "BaseComponent.h"

namespace dae {
	class GameObject;
}
class SpawnerComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	
	/// <summary>
	///
	/// </summary>
	/// <param name="spawnFunction">: The spawnfunction should return a GameObject ready to be added to the current scene</param>
	SpawnerComponent(std::function<std::shared_ptr<dae::GameObject>()> spawnFunction
		, int maxObjectsAlive = 1
		, int minSpawnTime = 0
		, int maxSpawnTime = 1);
	virtual ~SpawnerComponent();

	//------COPY CONSTRUCTORS------
	SpawnerComponent(const SpawnerComponent&) = delete;
	SpawnerComponent(SpawnerComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	SpawnerComponent operator=(const SpawnerComponent&) = delete;
	SpawnerComponent& operator=(SpawnerComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update();
	void Spawn();
	void ObjectDestroyed();

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	void SetNextSpawnTime();

	//------PRIVATE VARIABLES------	
	std::function<std::shared_ptr<dae::GameObject>()> m_SpawnFunction;
	int m_CurrentObjectsAlive;
	int m_MaxObjectsAlive;
	int m_MinSpawnTime;
	int m_MaxSpawnTime;
	float m_SpawnTimer;
};

