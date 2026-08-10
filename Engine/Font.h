#pragma once
#include "Resource.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace nu
{
    class Font : public Resource
    {
    public:
        Font() = default;
        ~Font();

        bool Load(const std::string& filename, float fontSize);
        void Close();

        TTF_Font* GetFont() const { return m_font; }

        friend class Text;

    private:
        TTF_Font* m_font{ nullptr };
    };
}