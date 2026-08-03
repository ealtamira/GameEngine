#pragma once
#include <vector>
#include <cstdint>
#include "Vector2.h"

namespace nu
{
    class Mesh
    {
    public:
        void AddPoint(const Vector2& point);

        void SetColor(uint8_t r, uint8_t g, uint8_t b);

        void Draw(class Renderer& renderer);

    private:
        std::vector<Vector2> m_points;
        uint8_t m_r = 255;
        uint8_t m_g = 255;
        uint8_t m_b = 255;
    };
}