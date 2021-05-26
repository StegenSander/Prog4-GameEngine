#include "MiniginPCH.h"
#include "SpawnerComponent.h"
#include "ExtraMath.h"
#include "GameTime.h"
#include "GameObject.h"
#include "SpawnedObjectComponent.h"
#include "Scene.h"



SpawnerComponent::SpawnerComponent(std::function<std::shared_ptr<dae::GameObject>()> spawnFunction, int maxObjectsAlive, int minSpawnTime, int maxSpawnTime)
	: m_SpawnFunction{ spawnFunction }
	, m_MaxObjectsAlive{ maxObjectsAlive }
	, m_MinSpawnTime{ minSpawnTime }
	, m_MaxSpawnTime{ maxSpawnTime }
	, m_CurrentObjectsAlive{ 0 }
{
	SetNextSpawnTime();
}

SpawnerComponent::~SpawnerComponent()
{
}

void SpawnerComponent::Update()
{
	if (!(m_CurrentObjectsAlive < m_MaxObjectsAlive)) return;
	m_SpawnTimer -= GameTime::GetInstance().GetDeltaTime();

	if (m_SpawnTimer <=0)
	{
		Spawn();
	}
}

void SpawnerComponent::Spawn()
{

	std::shared_ptr<dae::GameObject> obj = m_SpawnFunction();
	std::shared_ptr<SpawnedObjectComponent> spawnedObjComp(new SpawnedObjectComponent(this));
	obj->AddComponent(spawnedObjComp);

	m_pGameObject->GetScene()->AddObject(obj);
	m_CurrentObjectsAlive++;
	SetNextSpawnTime();
}

void SpawnerComponent::ObjectDestroyed()
{
	m_CurrentObjectsAlive--;
}

void SpawnerComponent::SetNextSpawnTime()
{
	m_SpawnTimer = ExtraMath::RandomFloat(m_MinSpawnTime, m_MaxSpawnTime);
}
