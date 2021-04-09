#pragma once
#include <XInput.h>
#include "Singleton.h"

#include <map>
#include "Commands.h"

#include "Controller.h"

namespace dae
{

    struct KeyboardKeyData
    {
        int SDLScancode;
        ButtonState buttonState = ButtonState::Down;
    };
    //We are using map so comparison needs to be supported
    inline bool operator< (const KeyboardKeyData& lhs, const KeyboardKeyData& rhs)
    {
        return lhs.SDLScancode < rhs.SDLScancode;
    }

	class InputManager final : public Singleton<InputManager>
	{
	public:

        ~InputManager();
        //General Functions
		bool ProcessInput();
        bool ProcessSDLInput();
        bool ProcessCommands();

        //KeyBoard functions
        bool IsKeyDown(int SDLScancode);

        //Command functions
		void AddCommand(ControllerButtonData buttonData, Command* pCommand,DWORD controllerIndex = 0);
        void AddCommand(KeyboardKeyData keyData, Command* pCommand);
        void MarkForDeleteByIdentifier(void* target);
        void RemoveMarkedCommands();

        void SetAmountOfControllers(DWORD amount);

	private:
        InputManager() = default;
        friend class Singleton<InputManager>;

        void HandleKeyPressed(int SDLScancode);
        void HandleKeyReleased(int SDLScancode);

        std::vector<Controller*> m_pControllers;

        using KeyboardCommandMap = std::map<KeyboardKeyData, std::unique_ptr<Command>>;
        KeyboardCommandMap m_KeyboardCommandMap{};

        DWORD m_AmountOfControllers = 0;
	};

}
