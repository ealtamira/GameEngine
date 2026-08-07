#pragma once
#include "Font.h"
#include <string>

struct SDL_Texture;

namespace nu
{
    class Renderer;

    struct Color { float r, g, b; };

    class Text
    {
    public:
        Text() = default;
        Text(res_t<Font> font) : m_font{ font } {}
        ~Text();

        bool Create(Renderer& renderer, const std::string& text, const Color& color);
        void Draw(Renderer& renderer, float x, float y);

    private:
        res_t<Font> m_font;
        SDL_Texture* m_texture{ nullptr };
    };
}