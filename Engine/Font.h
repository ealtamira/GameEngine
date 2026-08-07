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

        friend class Text;

    private:
        TTF_Font* m_font{ nullptr };
    };
}