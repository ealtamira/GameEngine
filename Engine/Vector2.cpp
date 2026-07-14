#include "pch.h"
#include "Vector2.h"
#include <stdexcept>
#include "Vector3.h"

namespace nu
{
    Vector2::Vector2() : x(0.0f), y(0.0f) {}
    Vector2::Vector2(float x, float y) : x(x), y(y) {}

    float& Vector2::operator[](int index)
    {
        if (index == 0) return x;
        if (index == 1) return y;
        throw std::out_of_range("Vector2 index out of range!");
    }

    bool Vector2::operator==(const Vector2& v) const { return (x == v.x && y == v.y); }
    bool Vector2::operator!=(const Vector2& v) const { return (x != v.x || y != v.y); }

    Vector2 Vector2::operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
    Vector2 Vector2::operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
    Vector2 Vector2::operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }
    Vector2 Vector2::operator/(float scalar) const { return Vector2(x / scalar, y / scalar); }

    Vector2& Vector2::operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
    Vector2& Vector2::operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
    Vector2& Vector2::operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    Vector2& Vector2::operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    float Vector2::Length() const { return std::sqrt(x * x + y * y); }
    float Vector2::LengthSqr() const { return (x * x + y * y); }

    Vector2 Vector2::Normalized() const
    {
        float len = Length();
        if (len == 0) return Vector2(0, 0);
        return Vector2(x / len, y / len);
    }

    float Vector2::Dot(const Vector2& v) const { return (x * v.x + y * v.y); }
    float Vector2::Angle() const { return std::atan2(y, x); }

    float Vector2::AngleBetween(const Vector2& v) const
    {
        float dot = Dot(v);
        float lengths = Length() * v.Length();
        if (lengths == 0) return 0.0f;
        return std::acos(dot / lengths);
    }

    Vector2 Vector2::Rotate(float angle) const
    {
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        return Vector2(x * cosA - y * sinA, x * sinA + y * cosA);
    }
}