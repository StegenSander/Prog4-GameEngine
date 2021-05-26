#include "MiniginPCH.h"
#include "GameControllerComponent.h"
#include "HealthEvents.h"

GameControllerComponent::GameControllerComponent()
	: Subject()
	, BaseComponent()
{
}

GameControllerComponent::~GameControllerComponent()
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
