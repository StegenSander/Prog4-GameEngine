#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	//PBYTE keyboardState{};
	//GetKeyboardState(keyboardState);

	//bool result = GetKeyState(0x41) & 0x8000;

	//std::cout << result;

	bool a = ProcessControllerInput();
	bool b = ProcessKeyBoardInput();
	bool c = ProcessCommands();

	return  !(!a || !b || !c);
}

bool dae::InputManager::ProcessControllerInput()
{
	DWORD result{};
	DWORD dword{ 0 };

	m_pPreviousInputState = std::move(m_pInputState);
	ZeroMemory(&m_pInputState, sizeof(m_pInputState));
	result = XInputGetState(dword, &m_pInputState);

	if (result == ERROR_SUCCESS)
	{
		//Controller connected
	}
	else
	{
		//No controller found
	}

	return true;
}

bool dae::InputManager::ProcessKeyBoardInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.scancode)
			{
			case SDL_SCANCODE_KP_1:
				break;
			case SDL_SCANCODE_KP_2:
				break;
			case SDL_SCANCODE_KP_3:
				break;
			default:
				break;
			}
		}

		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}

bool dae::InputManager::ProcessCommands()
{
	for (ControllerCommandMap::iterator mapIt = m_ControllerCommandMap.begin();
		mapIt != m_ControllerCommandMap.end(); mapIt++)
	{
		switch ((*mapIt).first.buttonState)
		{
		case ControllerButtonState::Down:
			if (IsButtonDown((*mapIt).first.buttonType)) (*mapIt).second->Execute();
			break;
		case ControllerButtonState::OnRelease:
			if (IsButtonReleased((*mapIt).first.buttonType)) (*mapIt).second->Execute();
			break;
		case ControllerButtonState::OnPress:
			if (IsButtonPressed((*mapIt).first.buttonType)) (*mapIt).second->Execute();
			break;
		case ControllerButtonState::OnPressAndRelease:
			if (IsButtonReleased((*mapIt).first.buttonType)
				|| IsButtonPressed((*mapIt).first.buttonType)) (*mapIt).second->Execute();
			break;
		}
	}

	return true;
}

bool dae::InputManager::IsButtonPressed(ControllerButton button) const
{
	return  m_pInputState.Gamepad.wButtons & WORD(button)
		&& !(m_pPreviousInputState.Gamepad.wButtons & WORD(button));
}

bool dae::InputManager::IsButtonReleased(ControllerButton button) const
{
	return  !(m_pInputState.Gamepad.wButtons & WORD(button))
		&& m_pPreviousInputState.Gamepad.wButtons & WORD(button);
}

bool dae::InputManager::IsButtonDown(ControllerButton button) const
{
	return m_pInputState.Gamepad.wButtons & WORD(button);
}

void dae::InputManager::AddCommand(ControllerButtonData buttonData, Command* pCommand)
{
	m_ControllerCommandMap.insert(std::make_pair(buttonData, pCommand));
}