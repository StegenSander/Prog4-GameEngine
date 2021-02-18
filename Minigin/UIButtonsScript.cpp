#include "MiniginPCH.h"
#include "UIButtonsScript.h"
#include "imgui.h"

void UIButtonScript::Render()
{
	ImGui::Button("single player");
	ImGui::Button("co-op");
	ImGui::Button("versus");
}
