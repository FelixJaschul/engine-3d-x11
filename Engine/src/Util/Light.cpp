#include <Util/Light.h>

namespace Engine::Util
{
    Light::Light()
        : m_position{ 300.0f, -100.0f, 200.0f }, m_direction{ 0.3f, 1.0f, 0.5f }, m_color(0xFFFFFFFF), m_intensity(1.0f), m_isDirectional(false)
    {
    }

    Light::Light(Math::Vec::Vec3 position, Math::Vec::Vec3 direction, uint32_t color, float intensity, bool isDirectional)
        : m_position(position), m_direction(direction), m_color(color), m_intensity(intensity), m_isDirectional(isDirectional)
    {
    }
}
