#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include <functional>

class ButtonComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	ButtonComponent(const glm::vec2& buttonOffset
		, const glm::vec2& buttonSize
		, const std::function<void()>& function);
	virtual ~ButtonComponent();

	//------COPY CONSTRUCTORS------
	ButtonComponent(const ButtonComponent&) = delete;
	ButtonComponent(ButtonComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	ButtonComponent operator=(const ButtonComponent&) = delete;
	ButtonComponent& operator=(ButtonComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	bool IsPressed(const glm::vec2& mousePos);

	//------PRIVATE VARIABLES------	
	std::function<void()> m_Function;
	glm::vec2 m_Offset;
	glm::vec2 m_Size;
};
