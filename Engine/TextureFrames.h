#pragma once
#include <vector>
#include <SDL3/SDL.h>

namespace nu
{
    class Texture;

    class TextureFrames {
    public:
        TextureFrames(Texture* texture);
        ~TextureFrames() = default;

        void AddFrame(const SDL_Rect& rect);

        const SDL_Rect& GetFrame(int index) const;

        size_t GetFrameCount() const;
        Texture* GetTexture() const;

    private:
        Texture* m_texture;
        std::vector<SDL_Rect> m_frames;
    };
}