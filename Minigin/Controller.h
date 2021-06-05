#pragma once

#include <XInput.h>
#include <map>
#include "Commands.h"

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

enum class ButtonState
{
    OnPress,
    OnRelease,
    OnPressAndRelease,
    Down,
};

struct JoystickValue
{
    float x;
    float y;
};

struct ControllerButtonData
{
    ControllerButton buttonType;
    ButtonState buttonState = ButtonState::Down;

    ControllerButtonData(ControllerButton button, ButtonState state)
        :buttonType{ button }
        , buttonState{ state }
    {
    }
};


//We are using map so comparison needs to be supported
inline bool operator< (const ControllerButtonData& lhs, const ControllerButtonData& rhs)
{
    return static_cast<WORD>(lhs.buttonType) < static_cast<WORD>(rhs.buttonType);
}

class Controller
{
public:
    Controller(DWORD controllerIndex)
        :m_ControllerIndex{ controllerIndex } {};
    ~Controller() = default;


    bool ProcessXINPUTInput();

    void ProcessCommands();
    void MarkForDeleteByIdentifier(void* target);
    void RemoveMarkedCommands();

    //Controller functions
    [[nodiscard]] bool IsControllerButtonPressed(ControllerButton button) const;
    [[nodiscard]] bool IsControllerButtonReleased(ControllerButton button) const;
    [[nodiscard]] bool IsControllerButtonDown(ControllerButton button) const;

    void AddCommand(ControllerButtonData buttonData, Command* pCommand);

    JoystickValue GetJoystickValues(bool isLeft = true) const;

private:
    DWORD m_ControllerIndex;

    //Controller input
    XINPUT_STATE m_pPreviousInputState{};
    XINPUT_STATE m_pInputState{};
    using ControllerCommandMap = std::map<ControllerButtonData, std::unique_ptr<Command>>;
    ControllerCommandMap m_ControllerCommandMap{};
};

