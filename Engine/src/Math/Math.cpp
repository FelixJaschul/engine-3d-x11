#include <Math/Math.h>

namespace Math
{
    float Radians(float degrees)
    {
        return degrees * (PI / 180.0f);
    }

    float Degrees(float radians)
    {
        return radians * (180.0f / PI);
    }

    float Clamp(float value, float min, float max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    float Lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }
}