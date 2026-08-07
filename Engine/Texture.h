#pragma once
#include "Resource.h"
#include "Vector2.h"
#include <string>

struct SDL_Texture;

namespace nu
{
    class Texture : public Resource
    {
    public:
        Texture() = default;
        ~Texture();

        bool Load(const std::string& filename, class Renderer& renderer);
        Vector2 GetSize();

        friend class Renderer;

    private:
        SDL_Texture* m_texture{ nullptr };
    };
}