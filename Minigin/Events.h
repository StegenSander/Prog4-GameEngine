#pragma once

struct EventData
{
	void* Sender;
};

enum class EventType
{
	PlayerDamageTaken,
	PlayerKilled,
	PlayerFallen,
};

