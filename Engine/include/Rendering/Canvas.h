#pragma once

#include <vector>
#include <cstdint>

namespace Engine::Rendering
{
    class Canvas
    {
    public:
        Canvas(int width, int height);
        ~Canvas() = default;

        void Clear(uint32_t color);
        void ClearDepth();
        void PutPixel(int x, int y, uint32_t color, float depth);

        [[nodiscard]] int GetWidth() const { return m_width; }
        [[nodiscard]] int GetHeight() const { return m_height; }
        [[nodiscard]] uint32_t* GetPixels() { return m_pixels.data(); }
        [[nodiscard]] const uint32_t* GetPixels() const { return m_pixels.data(); }

        void Resize(int width, int height);

    private:
        int m_width;
        int m_height;
        std::vector<uint32_t> m_pixels;
        std::vector<float> m_depthBuffer;
    };
}