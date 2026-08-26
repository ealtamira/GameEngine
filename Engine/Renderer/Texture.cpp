#include "pch.h"
#include "Texture.h"
#include "Renderer.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

namespace nu
{
    Texture::~Texture()
    {
        if (m_texture != nullptr)
        {
            SDL_DestroyTexture(m_texture);
        }
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (surface == nullptr)
        {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

        SDL_DestroySurface(surface);

        if (m_texture == nullptr)
        {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        return true;
    }

    Vector2 Texture::GetSize()
    {
        Vector2 v{ 0.0f, 0.0f };
        if (m_texture)
        {
            float w, h;
            SDL_GetTextureSize(m_texture, &w, &h);
            v.x = w;
            v.y = h;
        }
        return v;
    }
}