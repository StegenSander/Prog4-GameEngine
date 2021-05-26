#include "MiniginPCH.h"
#include "SpawnedObjectComponent.h"
#include "SpawnerComponent.h"

SpawnedObjectComponent::SpawnedObjectComponent(SpawnerComponent* owner)
	: m_Owner{owner}
{
}

SpawnedObjectComponent::~SpawnedObjectComponent()
{
	m_Owner->ObjectDestroyed();
}
