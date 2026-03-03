#pragma once

#include <algorithm>

namespace Math
{
    constexpr float PI = 3.14159265358979323846f;
    constexpr float TAU = 2.0f * PI;

    float Radians(float degrees);
    float Degrees(float radians);
    float Clamp(float value, float min, float max);
    float Lerp(float a, float b, float t);
}