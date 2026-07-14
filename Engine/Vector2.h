#pragma once
#include <cmath>

namespace nu
{
    struct Vector2
    {
        float x, y;

        Vector2();
        Vector2(float x, float y);

        float& operator[](int index); 
        bool operator==(const Vector2& v) const;
        bool operator!=(const Vector2& v) const;

        Vector2 operator+(const Vector2& v) const;
        Vector2 operator-(const Vector2& v) const;
        Vector2 operator*(float scalar) const;
        Vector2 operator/(float scalar) const;

        Vector2& operator+=(const Vector2& v);
        Vector2& operator-=(const Vector2& v);
        Vector2& operator*=(float scalar);
        Vector2& operator/=(float scalar);

        float Length() const;
        float LengthSqr() const;
        Vector2 Normalized() const;
        float Dot(const Vector2& v) const;
        float Angle() const;
        float AngleBetween(const Vector2& v) const;
        Vector2 Rotate(float angle) const; 
    };
}