#include <Rendering/Canvas.h>
#include <limits>
#include <algorithm>

namespace Engine::Rendering
{
    Canvas::Canvas(int width, int height)
        : m_width(width), m_height(height)
    {
        m_pixels.resize(width * height, 0);
        m_depthBuffer.resize(width * height, std::numeric_limits<float>::max());
    }

    void Canvas::Clear(uint32_t color)
    {
        std::fill(m_pixels.begin(), m_pixels.end(), color);
    }

    void Canvas::ClearDepth()
    {
        std::fill(m_depthBuffer.begin(), m_depthBuffer.end(), std::numeric_limits<float>::max());
    }

    void Canvas::PutPixel(int x, int y, uint32_t color, float depth)
    {
        if (x < 0 || y < 0 || x >= m_width || y >= m_height) return;

        int idx = y * m_width + x;
        if (depth < m_depthBuffer[idx])
        {
            m_depthBuffer[idx] = depth;
            m_pixels[idx] = color;
        }
    }

    void Canvas::Resize(int width, int height)
    {
        m_width = width;
        m_height = height;
        m_pixels.resize(width * height, 0);
        m_depthBuffer.resize(width * height, std::numeric_limits<float>::max());
    }
}