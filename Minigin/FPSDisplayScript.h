#pragma once
#include "BaseComponent.h"

class TextComponent;
class FPSDisplayScript
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	FPSDisplayScript(TextComponent* pTextComponent);
	virtual ~FPSDisplayScript() = default;

	//------COPY CONSTRUCTORS------
	FPSDisplayScript(const FPSDisplayScript&) = delete;
	FPSDisplayScript(FPSDisplayScript&&) = delete;
	//------ASSIGNMENT OPERATORS------
	FPSDisplayScript operator=(const FPSDisplayScript&) = delete;
	FPSDisplayScript& operator=(FPSDisplayScript&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------
	TextComponent* m_pTextComponent;
};

