#pragma once
#include "../Math/Color.h"
#include "Font.h"
#include "Renderer.h"
#include <string>
#include <memory>
#include <SDL3/SDL.h>

namespace nu
{
    class Text
    {
    public:
        Text(std::shared_ptr<Font> font);
        ~Text();

        bool Create(Renderer& renderer, const std::string& text, const Color& color);
        void Draw(Renderer& renderer, float x, float y);

    private:
        std::shared_ptr<Font> m_font;
        SDL_Texture* m_texture{ nullptr };
        int m_width{ 0 };
        int m_height{ 0 };
    };
}