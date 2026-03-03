#pragma once

#include <Math/Vec.h>
#include <Rendering/Canvas.h>
#include <Rendering/Camera.h>
#include <Util/Light.h>
#include <cstdint>

namespace Engine::World
{
    enum class WallType
    {
        Floor,
        WallX,
        WallZ
    };

    class Wall
    {
    public:
        Wall(Math::Vec::Vec3 position, float width, float height, float angle,
             WallType type, uint32_t color, bool flipCulling = false);
        ~Wall() = default;

        void Render(Rendering::Canvas* canvas, const Util::Light& light,
                   const Rendering::Camera& camera) const;

        [[nodiscard]] Math::Vec::Vec3 GetPosition() const { return m_position; }
        [[nodiscard]] float GetWidth() const { return m_width; }
        [[nodiscard]] float GetHeight() const { return m_height; }
        [[nodiscard]] float GetAngle() const { return m_angle; }
        [[nodiscard]] WallType GetType() const { return m_type; }
        [[nodiscard]] uint32_t GetColor() const { return m_color; }
        [[nodiscard]] bool GetFlipCulling() const { return m_flipCulling; }

        void SetPosition(Math::Vec::Vec3 position) { m_position = position; }
        void SetWidth(float width) { m_width = width; }
        void SetHeight(float height) { m_height = height; }
        void SetAngle(float angle) { m_angle = angle; }
        void SetColor(uint32_t color) { m_color = color; }
        void SetFlipCulling(bool flip) { m_flipCulling = flip; }

    private:
        Math::Vec::Vec3 m_position;
        float m_width;
        float m_height;
        float m_angle;
        WallType m_type;
        uint32_t m_color;
        bool m_flipCulling;
    };
}