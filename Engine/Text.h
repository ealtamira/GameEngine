#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Font.h"
#include "Color.h"
#include "Renderer.h"

namespace nu
{
    class Text
    {
    public:
        Text(std::shared_ptr<Font> font) : m_font{ font } {}
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