#pragma once
#include <cstdint> // For uint32_t

namespace Engine::Rendering
{
    extern float appFOV;
    extern float appZNear;
    extern float appZFar;
    extern bool appEnableLighting;
    extern bool appEnableFog;
    extern float appFogStart;
    extern float appFogEnd;
    extern uint32_t appFogColor;

    inline float GetFOV() { return appFOV; }
    inline float GetZNear() { return appZNear; }
    inline float GetZFar() { return appZFar; }
    inline bool GetEnableLighting() { return appEnableLighting; }
    inline bool GetEnableFog() { return appEnableFog; }
    inline float GetFogStart() { return appFogStart; }
    inline float GetFogEnd() { return appFogEnd; }
    inline uint32_t GetFogColor() { return appFogColor; }

    inline void SetFOV(float fov) { appFOV = fov; }
    inline void SetEnableLighting(bool enable) { appEnableLighting = enable; }
    inline void SetEnableFog(bool enable) { appEnableFog = enable; }
    inline void SetFogStart(float start) { appFogStart = start; }
    inline void SetFogEnd(float end) { appFogEnd = end; }
    inline void SetFogColor(uint32_t color) { appFogColor = color; }
}