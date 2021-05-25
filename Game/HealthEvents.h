#pragma once
#include "Events.h"

struct DamageTakenEvent : public EventData
{
	int healthRemaining;
};