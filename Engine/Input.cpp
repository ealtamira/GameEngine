#include "pch.h"
#include "Input.h"

namespace nu
{
    void Input::Update()
    {
        float mx, my;
        m_mouseState = SDL_GetMouseState(&mx, &my);
        m_mouseX = static_cast<float>(mx);
        m_mouseY = static_cast<float>(my);

        int numKeys;
        const bool* keyboardState = SDL_GetKeyboardState(&numKeys);
        m_prevKeyboardState = m_keyboardState;
        m_keyboardState.assign(keyboardState, keyboardState + numKeys);
    }

    bool Input::GetButtonDown(MouseButton button)
    {
        Uint32 sdlButton = 0;

        if (button == MouseButton::Left) sdlButton = SDL_BUTTON_LEFT;
        else if (button == MouseButton::Right) sdlButton = SDL_BUTTON_RIGHT;
        else if (button == MouseButton::Middle) sdlButton = SDL_BUTTON_MIDDLE;

        return (m_mouseState & sdlButton) != 0;
    }

    Vector2 Input::GetMousePosition()
    {
        return Vector2(m_mouseX, m_mouseY);
    }

    bool Input::GetKeyPressed(int scancode)
    {
        if (m_keyboardState.empty() || scancode >= m_keyboardState.size())
        {
            return false;
        }

        return m_keyboardState[scancode] && !m_prevKeyboardState[scancode];
    }
}