#pragma once
#include "BaseComponent.h"
class RenderComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	RenderComponent() = default;
	virtual ~RenderComponent() = default;

	//------PUBLIC FUNCTIONS------
	virtual void Update() override = 0;
	virtual void Render() = 0;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};

