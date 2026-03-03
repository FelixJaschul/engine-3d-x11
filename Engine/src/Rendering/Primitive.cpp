#include <Rendering/Primitive.h>
#include <Rendering/Triangle.h>

namespace Engine::Rendering
{
    void Primitive::DrawBackground(Canvas* canvas, uint32_t color)
    {
        canvas->Clear(color);
    }

    void Primitive::DrawFloor(Canvas* canvas, int tilesX, int tilesZ, float tileSize,float floorY, uint32_t color1, uint32_t color2, const Util::Light& light, const Camera& camera)
    {
        for (int tz = 0; tz < tilesZ; tz++)
        {
            for (int tx = -tilesX / 2; tx < tilesX / 2; tx++)
            {
                Math::Vec::Vec3 v0 = {
                    tx * tileSize - 1000.0f, floorY,
                    tz * tileSize + 4.0f - 500.0f - 1000.0f
                };

                Math::Vec::Vec3 v1 = v0 + Math::Vec::Vec3{ tileSize, 0, 0 };
                Math::Vec::Vec3 v2 = v0 + Math::Vec::Vec3{ tileSize, 0, tileSize };
                Math::Vec::Vec3 v3 = v0 + Math::Vec::Vec3{ 0, 0, tileSize };

                uint32_t color = ((tx + tz) & 1) ? color1 : color2;

                Math::Vec::Vec3 tri1[3] = { v0, v1, v2 };
                Math::Vec::Vec3 tri2[3] = { v0, v2, v3 };

                Triangle::Draw(canvas, tri1, color, light, camera);
                Triangle::Draw(canvas, tri2, color, light, camera);
            }
        }
    }
}
