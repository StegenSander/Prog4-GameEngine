#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


dae::InputManager::~InputManager()
{
	for (Controller* pContoller : m_pControllers)
	{
		delete pContoller;
	}
}

bool dae::InputManager::ProcessInput()
{
	for (Controller* pController : m_pControllers)
	{
		if (pController)
		{
			pController->ProcessXINPUTInput();
		}
	}

	ProcessCommands();

	return ProcessSDLInput();
}

bool dae::InputManager::ProcessSDLInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {

			HandleKeyPressed(e.key.keysym.scancode);
		}
		if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			HandleKeyReleased(e.key.keysym.scancode);
		}

		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		if (e.type == SDL_MOUSEMOTION)
		{

		}
	}

	return true;
}

bool dae::InputManager::ProcessCommands()
{
	for (Controller* pController : m_pControllers)
	{
		if (pController)
		{
			pController->ProcessCommands();
		}
	}

	//Pair: KeyboardKeyData, Command
	for (const auto& pair : m_KeyboardCommandMap)
	{
		if (pair.first.buttonState == ButtonState::Down)
		{
			if (IsKeyDown(pair.first.SDLScancode)) pair.second->Execute();
		}
	}

	return true;
}

bool dae::InputManager::IsKeyDown(int SDLScancode)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	return pStates[SDLScancode];
}

void dae::InputManager::AddCommand(ControllerButtonData buttonData, Command* pCommand, DWORD controllerIndex)
{
	if (controllerIndex < m_AmountOfControllers)
	{
		m_pControllers[controllerIndex]->AddCommand(buttonData, pCommand);
	}
}

void dae::InputManager::AddCommand(KeyboardKeyData keyData, Command* pCommand)
{
	m_KeyboardCommandMap.insert(std::make_pair(keyData, pCommand));
}
void dae::InputManager::MarkForDeleteByIdentifier(void* identifier)
{
	if (identifier == nullptr) return;
	for (Controller* pController : m_pControllers)
	{
		if (pController)
		{
			pController->MarkForDeleteByIdentifier(identifier);
		}
	}

	for (const auto& pair : m_KeyboardCommandMap)
	{
		if (pair.second->GetIdentifier() == identifier)
		{
			pair.second->MarkForDelete();
		}
	}
}

void dae::InputManager::RemoveMarkedCommands()
{
	for (Controller* pController : m_pControllers)
	{
		if (pController)
		{
			pController->RemoveMarkedCommands();
		}
	}

	std::vector<KeyboardKeyData> keysToDelete;
	for (const auto& pair : m_KeyboardCommandMap)
	{
		if (pair.second->IsMarkedForDelete())
		{
			m_KeyboardCommandMap.erase(pair.first);
		}
	}

	for (const KeyboardKeyData& key : keysToDelete)
	{
		m_KeyboardCommandMap.erase(key);
	}
}

void dae::InputManager::SetAmountOfControllers(DWORD amount)
{
	m_AmountOfControllers = amount;
	for (size_t i = 0; i < m_pControllers.size(); i++)
	{
		if (m_pControllers[i]) delete m_pControllers[i];
	}
	m_pControllers.clear();
	for (DWORD i = 0; i < amount; i++)
	{
		m_pControllers.push_back(new Controller(i));
	}
}

JoystickValue dae::InputManager::GetJoystickValue(DWORD index, bool isLeft)
{
	return m_pControllers[index]->GetJoystickValues(isLeft);
}

void dae::InputManager::HandleKeyPressed(int SDLScancode)
{
	//Pair: KeyboardKeyData, Command
	for (const auto& pair : m_KeyboardCommandMap)
	{
		if ( (pair.first.buttonState == ButtonState::OnPress
			|| pair.first.buttonState == ButtonState::OnPressAndRelease)
			&& pair.first.SDLScancode == SDLScancode)
		{
			pair.second->Execute();
		}
	}
}

void dae::InputManager::HandleKeyReleased(int SDLScancode)
{
	//Pair: KeyboardKeyData, Command
	for (const auto& pair : m_KeyboardCommandMap)
	{
		if ((pair.first.buttonState == ButtonState::OnRelease
			|| pair.first.buttonState == ButtonState::OnPressAndRelease)
			&& pair.first.SDLScancode == SDLScancode)
		{
			pair.second->Execute();
		}
	}
}
