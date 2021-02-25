#pragma once
#include "BaseComponent.h"

class UIButtonScript
	:public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	UIButtonScript() = default;
	virtual ~UIButtonScript() = default;

	//------COPY CONSTRUCTORS------
	UIButtonScript(const UIButtonScript&) = delete;
	UIButtonScript(UIButtonScript&&) = delete;
	//------ASSIGNMENT OPERATORS------
	UIButtonScript operator=(const UIButtonScript&) = delete;
	UIButtonScript& operator=(UIButtonScript&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void Update() override {}
	virtual void Render() override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};

