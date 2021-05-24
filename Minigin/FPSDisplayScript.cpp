#include "MiniginPCH.h"
#include "FPSDisplayScript.h"

#include "TextComponent.h"
#include "GameTime.h"

FPSDisplayScript::FPSDisplayScript(const std::shared_ptr<TextComponent>& pTextComponent)
	: m_pTextComponent(pTextComponent)
{
}

void FPSDisplayScript::Update()
{
	GameTime& pTime = GameTime::GetInstance();
	elapsedTime += pTime.GetDeltaTime();
	elapsedFrames++;

	if (elapsedTime > 1.f)
	{
		if (!m_pTextComponent.expired()) m_pTextComponent.lock()->SetText(std::to_string(elapsedFrames));
		elapsedFrames = 0;
		elapsedTime -= 1.f;
	}
}
