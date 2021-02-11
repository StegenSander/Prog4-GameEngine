#include "MiniginPCH.h"
#include "FPSDisplayScript.h"

#include "TextComponent.h"
#include "Time.h"

FPSDisplayScript::FPSDisplayScript(TextComponent* pTextComponent)
	: m_pTextComponent(pTextComponent)
{
}

void FPSDisplayScript::Update()
{
	if (m_pTextComponent) m_pTextComponent->SetText(std::to_string(int(std::round(Time::GetInstance().GetFPS()))));
}
