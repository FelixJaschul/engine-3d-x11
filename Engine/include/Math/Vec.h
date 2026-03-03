#pragma once

#include <cmath>

namespace Math::Vec
{
    struct Vec2 { float x, y; };
    struct Vec3 { float x, y, z; };

    struct iVec2 { int x, y; };
    struct iVec3 { int x, y, z; };

    // Vec3 operators
    Vec3 operator+(const Vec3& a, const Vec3& b);
    Vec3 operator-(const Vec3& a, const Vec3& b);
    Vec3 operator*(const Vec3& v, float s);
    Vec3 operator*(float s, const Vec3& v);
    Vec3 operator-(const Vec3& v);

    float Dot(const Vec3& a, const Vec3& b);
    Vec3 Cross(const Vec3& a, const Vec3& b);
    Vec3 Normalize(const Vec3& v);
    float Length(const Vec3& v);
    float Distance(const Vec3& a, const Vec3& b);
}