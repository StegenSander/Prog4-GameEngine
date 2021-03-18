#pragma once

#include "BaseComponent.h"
class ScoreComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	ScoreComponent();
	virtual ~ScoreComponent() {};

	//------COPY CONSTRUCTORS------
	ScoreComponent(const ScoreComponent&) = delete;
	ScoreComponent(ScoreComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	ScoreComponent operator=(const ScoreComponent&) = delete;
	ScoreComponent& operator=(ScoreComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override {};

	//Return the total score
	int ScorePoint(int amount);
	int GetScore() const;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	int m_Score;

	//------PRIVATE VARIABLES------	
};

