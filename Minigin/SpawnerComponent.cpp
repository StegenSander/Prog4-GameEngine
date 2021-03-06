#include "MiniginPCH.h"
#include "SpawnerComponent.h"
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
	if (obj->IsMarkedForDelete())
	{
		SetNextSpawnTime();
		return;
	}
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
	m_SpawnTimer = (rand() % ((m_MaxSpawnTime - m_MinSpawnTime) * 1000)) / float(1000) + m_MinSpawnTime;
}
