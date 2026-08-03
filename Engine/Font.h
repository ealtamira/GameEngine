#pragma once
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

namespace nu
{
    class Font
    {
    public:
        Font() = default;
        ~Font();

        bool Load(const std::string& filename, int fontSize);
        void Close();

        TTF_Font* GetFont() const { return m_font; }

    private:
        TTF_Font* m_font{ nullptr };
    };
}