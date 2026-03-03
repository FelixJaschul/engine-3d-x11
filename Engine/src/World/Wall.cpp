#include <World/Wall.h>
#include <Rendering/Triangle.h>
#include <Math/Math.h>
#include <cmath>
#include <algorithm>

namespace Engine::World
{
    Wall::Wall(Math::Vec::Vec3 position, float width, float height, float angle, WallType type, uint32_t color, bool flipCulling)
        : m_position(position), m_width(width), m_height(height), m_angle(angle), m_type(type), m_color(color), m_flipCulling(flipCulling)
    {
    }

    void Wall::Render(Rendering::Canvas* canvas, const Util::Light& light, const Rendering::Camera& camera) const
    {
        Math::Vec::Vec3 v0, v1, v2, v3;

        switch (m_type)
        {
            case WallType::Floor:
                v0 = { 0, 0, 0 };
                v1 = { m_width, 0, 0 };
                v2 = { m_width, 0, m_height };
                v3 = { 0, 0, m_height };
                break;

            case WallType::WallX:
                v0 = { 0, 0, 0 };
                v1 = { 0, 0, m_width };
                v2 = { 0, m_height, m_width };
                v3 = { 0, m_height, 0 };
                break;

            case WallType::WallZ:
                v0 = { 0, 0, 0 };
                v1 = { m_width, 0, 0 };
                v2 = { m_width, m_height, 0 };
                v3 = { 0, m_height, 0 };
                break;
        }

        Math::Vec::Vec3 verts[4] = { v0, v1, v2, v3 };

        // Rotate vertices
        for (int i = 0; i < 4; i++)
        {
            float x = verts[i].x;
            float z = verts[i].z;
            verts[i].x = x * std::cos(m_angle) - z * std::sin(m_angle);
            verts[i].z = x * std::sin(m_angle) + z * std::cos(m_angle);

            verts[i] = verts[i] + m_position;
        }

        // Flip culling if needed
        if (m_flipCulling)
        {
            std::swap(verts[1], verts[3]);
        }

        // Draw two triangles
        Math::Vec::Vec3 tri1[3] = { verts[0], verts[1], verts[2] };
        Math::Vec::Vec3 tri2[3] = { verts[0], verts[2], verts[3] };

        Rendering::Triangle::Draw(canvas, tri1, m_color, light, camera);
        Rendering::Triangle::Draw(canvas, tri2, m_color, light, camera);
    }
}
