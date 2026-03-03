#pragma once

#include <Rendering/Canvas.h>
#include <Rendering/Camera.h>
#include <Util/Light.h>
#include <cstdint>
namespace Engine::Rendering
{
    class Primitive
    {
    public:
        static void DrawBackground(Canvas* canvas, uint32_t color);

        static void DrawFloor(Canvas* canvas, int tilesX, int tilesZ, float tileSize, float floorY, uint32_t color1, uint32_t color2, const Util::Light& light, const Camera& camera);
    };
}
