#pragma once
#include <cmath>

namespace nu
{
    struct Vector2
    {
        float x;
        float y;

        Vector2();
        Vector2(float x, float y);

        float Length() const;
        Vector2 operator-(const Vector2& other) const;
    };
}