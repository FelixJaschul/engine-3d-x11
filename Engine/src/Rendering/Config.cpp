#include "Rendering/Config.h" // Include its own header for consistency

namespace Engine::Rendering
{
    float appFOV = 60.0f;
    float appZNear = 0.1f;
    float appZFar = 1000.0f;
    bool appEnableLighting = true;
    bool appEnableFog = true;
    float appFogStart = 400.0f;
    float appFogEnd = 1000.0f;
    uint32_t appFogColor = 0xFF78de99;
}