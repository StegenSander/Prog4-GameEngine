#pragma once
#include "ListenerComponent.h"

class ScoreboardComponent
	: public ListenerComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	ScoreboardComponent();
	virtual ~ScoreboardComponent() = default;

	//------COPY CONSTRUCTORS------
	ScoreboardComponent(const ScoreboardComponent&) = delete;
	ScoreboardComponent(ScoreboardComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	ScoreboardComponent operator=(const ScoreboardComponent&) = delete;
	ScoreboardComponent& operator=(ScoreboardComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Notify(EventType type, EventData* eventData) override;

	int GetScore() const { return m_Score; };

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------
	int m_Score = 0;
};

