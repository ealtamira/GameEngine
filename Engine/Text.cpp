#include "pch.h"
#include "Text.h"

namespace nu
{
    Text::~Text()
    {
        if (m_texture)
        {
            SDL_DestroyTexture(m_texture);
        }
    }

    bool Text::Create(Renderer& renderer, const std::string& text, const Color& color)
    {
        if (m_texture)
        {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }

        SDL_Color sdlColor = {
            static_cast<Uint8>(color.r * 255),
            static_cast<Uint8>(color.g * 255),
            static_cast<Uint8>(color.b * 255),
            static_cast<Uint8>(color.a * 255)
        };

        SDL_Surface* surface = TTF_RenderText_Blended(m_font->GetFont(), text.c_str(), text.length(), sdlColor);
        if (!surface) return false;

        m_texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
        m_width = surface->w;
        m_height = surface->h;

        SDL_DestroySurface(surface);

        return m_texture != nullptr;
    }

    void Text::Draw(Renderer& renderer, float x, float y)
    {
        if (!m_texture) return;

        SDL_FRect destRect = { x, y, static_cast<float>(m_width), static_cast<float>(m_height) };
        SDL_RenderTexture(renderer.GetRenderer(), m_texture, nullptr, &destRect);
    }
}