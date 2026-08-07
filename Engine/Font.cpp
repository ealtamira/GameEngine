#include "pch.h"
#include "Font.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

namespace nu
{
    Font::~Font()
    {
        Close();
    }

    void Font::Close()
    {
        if (m_font)
        {
            TTF_CloseFont(m_font);
            m_font = nullptr;
        }
    }

    bool Font::Load(const std::string& filename, float fontSize)
    {
        if (TTF_WasInit() == 0)
        {
            TTF_Init();
        }

        m_font = TTF_OpenFont(filename.c_str(), fontSize);

        if (!m_font)
        {
            std::cerr << "Failed to load font: " << filename << " | Error: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }
}