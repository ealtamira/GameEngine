#include "pch.h"
#include "Vector2.h"

namespace nu
{
    Vector2::Vector2() : x(0.0f), y(0.0f) {}
    Vector2::Vector2(float x, float y) : x(x), y(y) {}

    float Vector2::Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vector2 Vector2::operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }
}