#pragma once

#include <Math/Vec.h>

namespace Engine::Rendering
{
    class Camera
    {
        using Vec3 = Math::Vec::Vec3;
    public:
        Camera();
        ~Camera() = default;

        void Update(float deltaTime);

        [[nodiscard]] Vec3 GetPosition() const { return m_position; }
        [[nodiscard]] float GetAngleX() const { return m_angleX; }
        [[nodiscard]] float GetAngleY() const { return m_angleY; }
        [[nodiscard]] float GetFOV() const { return m_fov; }

        void SetPosition(Vec3 position) { m_position = position; }
        void SetAngleX(float angle) { m_angleX = angle; }
        void SetAngleY(float angle) { m_angleY = angle; }
        void SetFOV(float fov) { m_fov = fov; }

        void MoveForward(float amount);
        void MoveRight(float amount);
        void MoveUp(float amount);
        void RotateX(float amount);
        void RotateY(float amount);

        [[nodiscard]] Vec3 Project(const Vec3& worldPos, int screenWidth, int screenHeight) const;
        [[nodiscard]] bool IsBackFacing(const Vec3 tri[3]) const;

    private:
        Vec3 m_position;
        float m_angleX;
        float m_angleY;
        float m_fov;
    };
}