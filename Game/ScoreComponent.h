#pragma once
#include "BaseComponent.h"
class TextComponent;
class GameControllerComponent;

class ScoreComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	ScoreComponent(const std::weak_ptr<TextComponent>& textComp, int initialScore);
	virtual ~ScoreComponent();

	//------COPY CONSTRUCTORS------
	ScoreComponent(const ScoreComponent&) = delete;
	ScoreComponent(ScoreComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	ScoreComponent operator=(const ScoreComponent&) = delete;
	ScoreComponent& operator=(ScoreComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void Update() override;
	void AddScore(int amount);
	int GetScore();
	void ResetScore();

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	void UpdateText();

	//------PRIVATE VARIABLES------
	std::weak_ptr<TextComponent> m_TextComp;
	int m_Score;
};
