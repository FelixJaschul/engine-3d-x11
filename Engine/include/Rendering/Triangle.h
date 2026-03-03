#pragma once

#include <Math/Vec.h>
#include <Util/Light.h>
#include <Rendering/Camera.h>
#include <Rendering/Canvas.h>
#include <cstdint>

namespace Engine::Rendering
{
    class Triangle
    {
        using Vec3 = Math::Vec::Vec3;
    public:
        static void Draw(Canvas* canvas, const Vec3 tri[3], uint32_t color, const Util::Light& light, const Camera& camera);

        static uint32_t ApplyLighting(uint32_t baseColor, const Vec3& normal, const Vec3& position, const Util::Light& light);

        static uint32_t ApplyFog(uint32_t color, float distance);

        [[nodiscard]] static Vec3 CalculateNormal(const Vec3 tri[3]);

    private:
        static bool IsTriangleBehindCamera(const Vec3 tri[3], const Camera& camera);
    };
}
