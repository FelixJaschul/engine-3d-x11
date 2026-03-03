#include <Rendering/Triangle.h>
#include <algorithm>
#include <cmath>
#include <Math/Math.h>
#include <Rendering/Config.h>

namespace Engine::Rendering
{
    void Triangle::Draw(Canvas* canvas, const Vec3 tri[3], uint32_t color, const Util::Light& light, const Camera& camera)
    {
        if (camera.IsBackFacing(tri)) return;
        if (IsTriangleBehindCamera(tri, camera)) return;

        Vec3 normal = CalculateNormal(tri);
        Vec3 center = {
            (tri[0].x + tri[1].x + tri[2].x) / 3.0f,
            (tri[0].y + tri[1].y + tri[2].y) / 3.0f,
            (tri[0].z + tri[1].z + tri[2].z) / 3.0f
        };

        uint32_t litColor = ApplyLighting(color, normal, center, light);

        Vec3 screen[3];
        for (int i = 0; i < 3; i++)
        {
            screen[i] = camera.Project(tri[i], canvas->GetWidth(), canvas->GetHeight());
        }

        int minX = std::max(0, static_cast<int>(std::floor(std::min({screen[0].x, screen[1].x, screen[2].x}))));
        int minY = std::max(0, static_cast<int>(std::floor(std::min({screen[0].y, screen[1].y, screen[2].y}))));
        int maxX = std::min(canvas->GetWidth() - 1, static_cast<int>(std::ceil(std::max({screen[0].x, screen[1].x, screen[2].x}))));
        int maxY = std::min(canvas->GetHeight() - 1, static_cast<int>(std::ceil(std::max({screen[0].y, screen[1].y, screen[2].y}))));

        float denom = ((screen[1].y - screen[2].y) * (screen[0].x - screen[2].x) + (screen[2].x - screen[1].x) * (screen[0].y - screen[2].y));

        if (std::fabs(denom) < 1e-6f) return;

        for (int y = minY; y <= maxY; y++)
        {
            for (int x = minX; x <= maxX; x++)
            {
                float alpha = ((screen[1].y - screen[2].y) * (x - screen[2].x) +
                              (screen[2].x - screen[1].x) * (y - screen[2].y)) / denom;
                float beta = ((screen[2].y - screen[0].y) * (x - screen[2].x) +
                             (screen[0].x - screen[2].x) * (y - screen[2].y)) / denom;
                float gamma = 1.0f - alpha - beta;

                if (alpha >= 0 && beta >= 0 && gamma >= 0)
                {
                    float z = alpha * screen[0].z + beta * screen[1].z + gamma * screen[2].z;
                    float dist = Math::Vec::Distance(center, camera.GetPosition());
                    uint32_t fogColor = ApplyFog(litColor, dist);

                    canvas->PutPixel(x, y, fogColor, z);
                }
            }
        }
    }

    uint32_t Triangle::ApplyLighting(uint32_t baseColor, const Vec3& normal, const Vec3& position, const Util::Light& light)
    {
        if (!GetEnableLighting()) return baseColor;

        Vec3 lightDir;
        if (light.IsDirectional()) lightDir = -light.GetDirection();
        else lightDir = light.GetPosition() - position;

        lightDir = Math::Vec::Normalize(lightDir);

        float diffuse = std::max(0.0f, Math::Vec::Dot(normal, lightDir));
        float ambient = 0.2f;
        float intensity = ambient + diffuse * light.GetIntensity() * (1.0f - ambient);

        uint8_t r = ((baseColor >> 16) & 0xFF);
        uint8_t g = ((baseColor >> 8) & 0xFF);
        uint8_t b = (baseColor & 0xFF);

        r = static_cast<uint8_t>(r * intensity);
        g = static_cast<uint8_t>(g * intensity);
        b = static_cast<uint8_t>(b * intensity);

        uint8_t lr = (light.GetColor() >> 16) & 0xFF;
        uint8_t lg = (light.GetColor() >> 8) & 0xFF;
        uint8_t lb = light.GetColor() & 0xFF;

        r = (r * lr) >> 8;
        g = (g * lg) >> 8;
        b = (b * lb) >> 8;

        return 0xFF000000 | (r << 16) | (g << 8) | b;
    }

    uint32_t Triangle::ApplyFog(uint32_t color, float distance)
    {
        if (!GetEnableFog()) return color;

        float fogStart = GetFogStart();
        float fogEnd = GetFogEnd();

        if (distance <= fogStart) return color;
        if (distance >= fogEnd) return GetFogColor();

        float fogFactor = (distance - fogStart) / (fogEnd - fogStart);
        fogFactor = Math::Clamp(fogFactor, 0.0f, 1.0f);

        uint32_t r1 = (color >> 16) & 0xFF;
        uint32_t g1 = (color >> 8) & 0xFF;
        uint32_t b1 = color & 0xFF;

        uint32_t fogColor = GetFogColor();
        uint32_t r2 = (fogColor >> 16) & 0xFF;
        uint32_t g2 = (fogColor >> 8) & 0xFF;
        uint32_t b2 = fogColor & 0xFF;

        auto factorInt = static_cast<uint32_t>(fogFactor * 256);
        uint32_t invFactor = 256 - factorInt;

        uint32_t nr = ((r1 * invFactor + r2 * factorInt) >> 8);
        uint32_t ng = ((g1 * invFactor + g2 * factorInt) >> 8);
        uint32_t nb = ((b1 * invFactor + b2 * factorInt) >> 8);

        return (0xFF << 24) | (nr << 16) | (ng << 8) | nb;
    }

    Triangle::Vec3 Triangle::CalculateNormal(const Vec3 tri[3])
    {
        Vec3 e1 = tri[1] - tri[0];
        Vec3 e2 = tri[2] - tri[0];
        Vec3 n = Math::Vec::Cross(e1, e2);
        return Math::Vec::Normalize(n);
    }

    bool Triangle::IsTriangleBehindCamera(const Vec3 tri[3], const Camera& camera)
    {
        float zNear = GetZNear();
        Vec3 camPos = camera.GetPosition();

        for (int i = 0; i < 3; i++)
        {
            Vec3 rel = tri[i] - camPos;

            float cosX = std::cos(camera.GetAngleX());
            float sinX = std::sin(camera.GetAngleX());
            float cosY = std::cos(camera.GetAngleY());
            float sinY = std::sin(camera.GetAngleY());

            float tmpX = rel.x * cosX - rel.z * sinX;
            float tmpZ = rel.x * sinX + rel.z * cosX;
            rel.x = tmpX;
            rel.z = tmpZ;

            float tmpY = rel.y * cosY - rel.z * sinY;
            tmpZ = rel.y * sinY + rel.z * cosY;
            rel.y = tmpY;
            rel.z = tmpZ;

            if (rel.z <= zNear * 0.5f) return true;
        }
        return false;
    }
}
