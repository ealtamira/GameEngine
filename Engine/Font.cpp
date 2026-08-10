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
            SDL_Log("Failed to load font: %s | Error: %s", filename.c_str(), SDL_GetError());
            return false;
        }

        return true;
    }
}