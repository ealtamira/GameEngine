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
}