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
	Time& pTime = Time::GetInstance();
	elapsedTime += pTime.GetDeltaTime();
	elapsedFrames++;

	if (elapsedTime > 1.f)
	{
		if (m_pTextComponent) m_pTextComponent->SetText(std::to_string(elapsedFrames));
		elapsedFrames = 0;
		elapsedTime -= 1.f;
	}
}
