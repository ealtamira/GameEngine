#include "pch.h"
#include "TextureFrames.h"

namespace nu
{
    TextureFrames::TextureFrames(Texture* texture) : m_texture(texture)
    {
    }

    void TextureFrames::AddFrame(const SDL_Rect& rect)
    {
        m_frames.push_back(rect);
    }

    const SDL_Rect& TextureFrames::GetFrame(int index) const
    {
        return m_frames[index];
    }

    size_t TextureFrames::GetFrameCount() const
    {
        return m_frames.size();
    }

    Texture* TextureFrames::GetTexture() const
    {
        return m_texture;
    }
}