#include "MiniginPCH.h"
#include "GameControllerComponent.h"
#include "HealthEvents.h"
#include "SceneManager.h"

GameControllerComponent::GameControllerComponent()
	: Subject()
	, BaseComponent()
{
}


void GameControllerComponent::PlayerKilled()
{
	Notify(EventType::PlayerKilled);
}

void GameControllerComponent::PlayerDamaged()
{
	Notify(EventType::PlayerDamageTaken);
}

void GameControllerComponent::PlayerOffMap()
{
	Notify(EventType::PlayerFallen);
}
