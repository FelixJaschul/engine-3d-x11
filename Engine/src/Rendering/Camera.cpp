#include <Rendering/Camera.h>
#include <cmath>
#include <Math/Math.h>
#include <Rendering/Config.h>

namespace Engine::Rendering
{
    Camera::Camera()
        : m_position{ 0.0f, 0.0f, 0.0f }, m_angleX(210.0f * Math::PI / 180.0f), m_angleY(0.0f), m_fov(60.0f * Math::PI / 180.0f)
    {
    }

    void Camera::Update(float deltaTime)
    {
        // This is called from App, but actual movement is handled by input
    }

    void Camera::MoveForward(float amount)
    {
        float cosX = std::cos(m_angleX);
        float sinX = std::sin(m_angleX);
        m_position.x += sinX * amount;
        m_position.z += cosX * amount;
    }

    void Camera::MoveRight(float amount)
    {
        float cosX = std::cos(m_angleX);
        float sinX = std::sin(m_angleX);
        m_position.x += cosX * amount;
        m_position.z -= sinX * amount;
    }

    void Camera::MoveUp(float amount)
    {
        m_position.y += amount;
    }

    void Camera::RotateX(float amount)
    {
        m_angleX += amount;
    }

    void Camera::RotateY(float amount)
    {
        m_angleY += amount;
        m_angleY = Math::Clamp(m_angleY, -Math::PI / 2.0f + 0.1f, Math::PI / 2.0f - 0.1f);
    }

    Math::Vec::Vec3 Camera::Project(const Math::Vec::Vec3& worldPos, int screenWidth, int screenHeight) const
    {
        float focalLength = screenHeight / (2.0f * std::tan(m_fov / 2.0f));

        Math::Vec::Vec3 rel = worldPos - m_position;

        // Rotate around Y axis (horizontal rotation)
        float cosX = std::cos(m_angleX);
        float sinX = std::sin(m_angleX);
        float tmpX = rel.x * cosX - rel.z * sinX;
        float tmpZ = rel.x * sinX + rel.z * cosX;
        rel.x = tmpX;
        rel.z = tmpZ;

        // Rotate around X axis (vertical rotation)
        float cosY = std::cos(m_angleY);
        float sinY = std::sin(m_angleY);
        float tmpY = rel.y * cosY - rel.z * sinY;
        tmpZ = rel.y * sinY + rel.z * cosY;
        rel.y = tmpY;
        rel.z = tmpZ;

        float zNear = Engine::Rendering::GetZNear();
        float zFar = Engine::Rendering::GetZFar();

        if (rel.z < zNear) rel.z = zNear;

        float invZ = 1.0f / rel.z;
        float sx = (rel.x * focalLength * invZ) + screenWidth * 0.5f;
        float sy = (rel.y * focalLength * invZ) + screenHeight * 0.5f;
        float sz = (rel.z - zNear) / (zFar - zNear);

        return { sx, sy, sz };
    }

    bool Camera::IsBackFacing(const Math::Vec::Vec3 tri[3]) const
    {
        Math::Vec::Vec3 e1 = tri[1] - tri[0];
        Math::Vec::Vec3 e2 = tri[2] - tri[0];
        Math::Vec::Vec3 n = Math::Vec::Cross(e1, e2);

        Math::Vec::Vec3 dir = m_position - tri[0];
        return Math::Vec::Dot(n, dir) <= 0.0f;
    }
}
