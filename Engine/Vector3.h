#pragma once
#include <cmath>

namespace nu
{
    struct Vector3
    {
        float x, y, z;

        Vector3();
        Vector3(float x, float y, float z);

        float& operator[](int index);
        bool operator==(const Vector3& v) const;
        bool operator!=(const Vector3& v) const;

        Vector3 operator+(const Vector3& v) const;
        Vector3 operator-(const Vector3& v) const;
        Vector3 operator*(float scalar) const;
        Vector3 operator/(float scalar) const;

        Vector3& operator+=(const Vector3& v);
        Vector3& operator-=(const Vector3& v);
        Vector3& operator*=(float scalar);
        Vector3& operator/=(float scalar);

        Vector3 operator+(float scalar) const;
        Vector3 operator-(float scalar) const;
        Vector3& operator+=(float scalar);
        Vector3& operator-=(float scalar);

        Vector3 operator*(const Vector3& v) const;
        Vector3 operator/(const Vector3& v) const;
        Vector3& operator*=(const Vector3& v);
        Vector3& operator/=(const Vector3& v);

        float Length() const;
        float LengthSqr() const;
        Vector3 Normalized() const;
        float Dot(const Vector3& v) const;
    };
}