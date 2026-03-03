#pragma once

#include <Math/Vec.h>
#include <cstdint>

namespace Engine::Util
{
    class Light
    {
        using Vec3 = Math::Vec::Vec3;
    public:
        Light();
        Light(Vec3 position, Vec3 direction, uint32_t color, float intensity, bool isDirectional);
        ~Light() = default;

        [[nodiscard]] Vec3 GetPosition() const { return m_position; }
        [[nodiscard]] Vec3 GetDirection() const { return m_direction; }
        [[nodiscard]] uint32_t GetColor() const { return m_color; }
        [[nodiscard]] float GetIntensity() const { return m_intensity; }
        [[nodiscard]] bool IsDirectional() const { return m_isDirectional; }

        void SetPosition(Vec3 position) { m_position = position; }
        void SetDirection(Vec3 direction) { m_direction = direction; }
        void SetColor(uint32_t color) { m_color = color; }
        void SetIntensity(float intensity) { m_intensity = intensity; }
        void SetIsDirectional(bool isDirectional) { m_isDirectional = isDirectional; }

    private:
        Vec3 m_position;
        Vec3 m_direction;
        uint32_t m_color;
        float m_intensity;
        bool m_isDirectional;
    };
}