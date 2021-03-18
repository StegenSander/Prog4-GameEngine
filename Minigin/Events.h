#pragma once

struct EventData
{
	void* Sender;
};

struct PlayerDamageData
	: EventData
{
	int RemainingHealth;
	int DamageDone;
};

struct ScorePointData
	: EventData
{
	int PointsScored;
	int currentScore;
};

enum class EventType
{
	ScorePoint,
	PlayerDamage,
	PlayerDied,
};

