#pragma once
#include "../Resources/Resource.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace nu
{
    class Font : public Resource
    {
    public:
        Font() = default;
        ~Font();

        Font(const Font&) = delete;
        Font& operator=(const Font&) = delete;

        Font(Font&& other) noexcept : m_font(other.m_font) { other.m_font = nullptr; }
        Font& operator=(Font&& other) noexcept {
            if (this != &other) {
                Close();
                m_font = other.m_font;
                other.m_font = nullptr;
            }
            return *this;
        }

        bool Load(const std::string& filename, float fontSize);
        void Close();

        TTF_Font* GetFont() const { return m_font; }

        friend class Text;

    private:
        TTF_Font* m_font{ nullptr };
    };
}