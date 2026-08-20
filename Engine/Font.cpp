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

        TTF_Font* loadedFont = TTF_OpenFont(filename.c_str(), fontSize);

        if (!loadedFont)
        {
            SDL_Log("Failed to load font: %s | Error: %s", filename.c_str(), SDL_GetError());
            m_font = nullptr;
            return false;
        }

        m_font = loadedFont;
        return true;
    }
}