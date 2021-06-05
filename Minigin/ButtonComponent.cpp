#include "MiniginPCH.h"
#include "ButtonComponent.h"
#include "InputManager.h"
#include "Scene.h"

ButtonComponent::ButtonComponent(const glm::vec2& buttonOffset
	, const glm::vec2& buttonSize,const std::function<void()>& function)
	: m_Function{function}
	, m_Offset {buttonOffset}
	, m_Size{buttonSize}
{
}

void ButtonComponent::Update()
{
	auto input = m_pGameObject->GetScene()->GetSceneData()->pInputManager;
	const glm::vec2& mousePos = input->GetMousePosition();
	if (input->IsMouseButtonDown(1) && IsPressed(mousePos))
	{
		m_Function();
	}
}

bool ButtonComponent::IsPressed(const glm::vec2& mousePos) const
{
	glm::vec2 positon =
	{ 
		m_pGameObject->GetTransform().GetPosition().x + m_Offset.x,
		m_pGameObject->GetTransform().GetPosition().y + m_Offset.y
	};
	return (mousePos.x > positon.x && mousePos.x < positon.x + m_Size.x
		&& mousePos.y > positon.y && mousePos.y < positon.y + m_Size.y);
}
