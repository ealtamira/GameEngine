#pragma once
#include <SDL3/SDL.h>
#include "Vector2.h"
#include <vector>

namespace nu
{
    class Input
    {
    public:
        enum class MouseButton
        {
            Left,
            Right,
            Middle
        };

        void Update();
        bool GetButtonDown(MouseButton button);
        Vector2 GetMousePosition();

        bool GetKeyPressed(int scancode);

    private:
        Uint32 m_mouseState = 0;
        float m_mouseX = 0.0f;
        float m_mouseY = 0.0f;

        std::vector<Uint8> m_keyboardState;
        std::vector<Uint8> m_prevKeyboardState;
    };
}