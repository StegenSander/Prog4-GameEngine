#include "MiniginPCH.h"
#include "Controller.h"




bool Controller::ProcessXINPUTInput()
{
	DWORD result{};

	m_pPreviousInputState = std::move(m_pInputState);
	ZeroMemory(&m_pInputState, sizeof(m_pInputState));


	result = XInputGetState(m_ControllerIndex, &m_pInputState);

	if (result == ERROR_SUCCESS)
	{
		//Controller connected
	}
	else
	{
		//No controller found
		return false;
	}

	return true;
}

void Controller::ProcessCommands()
{
	//Pair: ControllerButtonData, Command
	for (const auto& pair : m_ControllerCommandMap)
	{
		switch (pair.first.buttonState)
		{
		case ButtonState::Down:
			if (IsControllerButtonDown(pair.first.buttonType)) pair.second->Execute();
			break;
		case ButtonState::OnRelease:
			if (IsControllerButtonReleased(pair.first.buttonType)) pair.second->Execute();
			break;
		case ButtonState::OnPress:
			if (IsControllerButtonPressed(pair.first.buttonType)) pair.second->Execute();
			break;
		case ButtonState::OnPressAndRelease:
			if (IsControllerButtonReleased(pair.first.buttonType)
				|| IsControllerButtonPressed(pair.first.buttonType)) pair.second->Execute();
			break;
		}
	}
}

bool Controller::IsControllerButtonPressed(ControllerButton button) const
{
	return  m_pInputState.Gamepad.wButtons & WORD(button)
		&& !(m_pPreviousInputState.Gamepad.wButtons & WORD(button));
}

bool Controller::IsControllerButtonReleased(ControllerButton button) const
{
	return  !(m_pInputState.Gamepad.wButtons & WORD(button))
		&& m_pPreviousInputState.Gamepad.wButtons & WORD(button);
}

bool Controller::IsControllerButtonDown(ControllerButton button) const
{
	return m_pInputState.Gamepad.wButtons & WORD(button);
}

void Controller::AddCommand(ControllerButtonData buttonData, Command* pCommand)
{
	m_ControllerCommandMap.insert(std::make_pair(buttonData, pCommand));
}
