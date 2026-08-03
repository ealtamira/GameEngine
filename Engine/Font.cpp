#include "pch.h"
#include "Font.h"
#include <iostream>

namespace nu
{
    Font::~Font()
    {
        Close();
    }

    bool Font::Load(const std::string& filename, int fontSize)
    {
        if (TTF_WasInit() == 0)
        {
            TTF_Init();
        }

        m_font = TTF_OpenFont(filename.c_str(), static_cast<float>(fontSize)); 
        if (!m_font)
        {
            std::cerr << "Failed to load font: " << filename << " | Error: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    void Font::Close()
    {
        if (m_font)
        {
            TTF_CloseFont(m_font);
            m_font = nullptr;
        }
    }
}