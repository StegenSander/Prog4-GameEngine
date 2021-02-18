#pragma once
#include <XInput.h>
#include "Singleton.h"

#include <map>
#include "Commands.h"

namespace dae
{
    enum class ControllerButton
    {
        ButtonA = XINPUT_GAMEPAD_A,
        ButtonB = XINPUT_GAMEPAD_B,
        ButtonX = XINPUT_GAMEPAD_X,
        ButtonY = XINPUT_GAMEPAD_Y,
        Up = XINPUT_GAMEPAD_DPAD_UP,
        Down = XINPUT_GAMEPAD_DPAD_DOWN,
        Left = XINPUT_GAMEPAD_DPAD_LEFT,
        Right = XINPUT_GAMEPAD_DPAD_RIGHT,
        LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
        RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
        LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
        RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
        Start = XINPUT_GAMEPAD_START,
        Back = XINPUT_GAMEPAD_BACK
    };

    enum class ControllerButtonState
    {
        OnPress,
        OnRelease,
        OnPressAndRelease,
        Down,
    };

    struct ControllerButtonData
    {
        ControllerButton buttonType;
        ControllerButtonState buttonState = ControllerButtonState::Down;
    };

    //We are using map so comparison needs to be supported
    inline bool operator< (const ControllerButtonData& lhs, const ControllerButtonData& rhs)
    {
        return WORD(lhs.buttonType) < WORD(rhs.buttonType);
    }

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
        bool ProcessControllerInput();
        bool ProcessKeyBoardInput();

        bool ProcessCommands();

		bool IsButtonPressed(ControllerButton button) const;
		bool IsButtonReleased(ControllerButton button) const;
		bool IsButtonDown(ControllerButton button) const;

		void AddCommand(ControllerButtonData buttonData, Command* pCommand);

	private:
        //Controller input
		XINPUT_STATE m_pPreviousInputState;
		XINPUT_STATE m_pInputState;
		using ControllerCommandMap = std::map<ControllerButtonData, std::unique_ptr<Command>>;
		ControllerCommandMap m_ControllerCommandMap{};

	};

}
