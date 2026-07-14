#include "pch.h"
#include "Vector3.h"
#include <stdexcept>

namespace nu
{
    Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    float& Vector3::operator[](int index)
    {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::out_of_range("Vector3 index out of range!");
    }

    bool Vector3::operator==(const Vector3& v) const { return (x == v.x && y == v.y && z == v.z); }
    bool Vector3::operator!=(const Vector3& v) const { return (x != v.x || y != v.y || z != v.z); }

    Vector3 Vector3::operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 Vector3::operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 Vector3::operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
    Vector3 Vector3::operator/(float scalar) const { return Vector3(x / scalar, y / scalar, z / scalar); }

    Vector3& Vector3::operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& Vector3::operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vector3& Vector3::operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    Vector3& Vector3::operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

    float Vector3::Length() const { return std::sqrt(x * x + y * y + z * z); }
    float Vector3::LengthSqr() const { return (x * x + y * y + z * z); }

    Vector3 Vector3::Normalized() const
    {
        float len = Length();
        if (len == 0) return Vector3(0, 0, 0);
        return Vector3(x / len, y / len, z / len);
    }

    float Vector3::Dot(const Vector3& v) const { return (x * v.x + y * v.y + z * v.z); }
}