#pragma once
#include "Singleton.h"

class ListenerComponent;

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
	int PointsScore;
};

enum class EventType
{
	ScorePoint,
	PlayerDamage,
	PlayerDied,
};

class Observer
	: public dae::Singleton<Observer>
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	virtual ~Observer() = default;

	//------PUBLIC FUNCTIONS------
	void Notify(EventType type, EventData* eventData = nullptr);

	void AddListener(ListenerComponent* listener);
	void RemoveListener(ListenerComponent* listener);
	

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	friend class dae::Singleton<Observer>;
	Observer() = default;

	//------PRIVATE VARIABLES------	
	std::vector<ListenerComponent*> m_pListeners;
};

