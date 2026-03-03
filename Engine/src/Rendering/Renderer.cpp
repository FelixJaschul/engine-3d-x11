#include <Rendering/Renderer.h>
#include <Config.h>
#include <cstring>
#include <iostream>
#include <memory>

namespace Engine::Rendering
{
    Renderer::Renderer(Window* window)
        : m_display(window->GetDisplay()), m_window(window->GetWindow()), m_screen(DefaultScreen(m_display)), m_image(nullptr), m_width(window->GetWidth()), m_height(window->GetHeight())
    {
        if (!m_display || !m_window)
        {
            std::cerr << "[Renderer] Invalid Window or Display." << std::endl;
            return;
        }

        m_gc = XDefaultGC(m_display, m_screen);
        m_canvas = std::make_unique<Canvas>(m_width, m_height);

        XVisualInfo visInfo;
        if (!XMatchVisualInfo(m_display, m_screen, 24, TrueColor, &visInfo))
        {
            std::cerr << "[Renderer] No matching visual info." << std::endl;
            return;
        }

        m_image = XCreateImage(
            m_display,
            visInfo.visual,
            visInfo.depth,
            ZPixmap,
            0,
            reinterpret_cast<char*>(m_canvas->GetPixels()),
            m_width,
            m_height,
            32,
            0
        );

        std::cout << "[Renderer] Initialized successfully." << std::endl;
    }

    Renderer::~Renderer()
    {
        if (m_image)
        {
            m_image->data = nullptr; // save way to not delete canvas
            XDestroyImage(m_image);
        }
    }

    void Renderer::SetColor(const unsigned long color) const
    {
        XSetForeground(m_display, m_gc, color);
    }

    void Renderer::DrawText(const int x, const int y, const char* text, const unsigned long color) const
    {
        if (!text) return;
        SetColor(color);
        XDrawString(m_display, m_window, m_gc, x, y, text, static_cast<int>(strlen(text)));
    }

    void Renderer::DrawTriangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const unsigned long color) const
    {
        SetColor(color);
        if (GetWireframeMode())
        {
            XDrawLine(m_display, m_window, m_gc, x1, y1, x2, y2);
            XDrawLine(m_display, m_window, m_gc, x2, y2, x3, y3);
            XDrawLine(m_display, m_window, m_gc, x3, y3, x1, y1);
        }
        else
        {
            XFillPolygon(m_display, m_window, m_gc, (XPoint[]) {
                    { static_cast<short>(x1), static_cast<short>(y1) },
                    { static_cast<short>(x2), static_cast<short>(y2) },
                    { static_cast<short>(x3), static_cast<short>(y3) } },
                3, Convex, CoordModeOrigin
            );
        }
    }

    void Renderer::DrawRect(const int x, const int y, const int width, const int height, const unsigned long color) const
    {
        if (x + width < 0 || y + height < 0 || x >= Engine::Window::GetDefaultWindowX() || y >= Engine::Window::GetDefaultWindowY())
        {
            return;
        }

        SetColor(color);
        if (GetWireframeMode())
        {
            XDrawRectangle(m_display, m_window, m_gc, x, y, static_cast<unsigned int>(width), static_cast<unsigned int>(height));
        }
        else
        {
            XFillRectangle(m_display, m_window, m_gc, x, y, static_cast<unsigned int>(width), static_cast<unsigned int>(height));
        }
    }

    void Renderer::Clear() const
    {
        XClearWindow(m_display, m_window);
    }

    void Renderer::Present() const
    {
        XFlush(m_display);
    }

    void Renderer::Present(Canvas* canvas)
    {
        if (!m_image) return;

        // if canvas was resized pointer gets reinitialized 
        m_image->data = reinterpret_cast<char*>(canvas->GetPixels());
        m_image->width = canvas->GetWidth();
        m_image->height = canvas->GetHeight();

        XPutImage(m_display, m_window, m_gc, m_image, 0, 0, 0, 0, canvas->GetWidth(), canvas->GetHeight());
        XFlush(m_display);
    }

    void Renderer::OnResize(int width, int height)
    {
        m_width = width;
        m_height = height;

        if (m_canvas)
        {
            m_canvas->Resize(width, height);
        }

        if (m_image)
        {
            m_image->data = nullptr;
            XDestroyImage(m_image);

            XVisualInfo visInfo;
            if (XMatchVisualInfo(m_display, m_screen, 24, TrueColor, &visInfo))
            {
                m_image = XCreateImage(
                    m_display,
                    visInfo.visual,
                    visInfo.depth,
                    ZPixmap,
                    0,
                    reinterpret_cast<char*>(m_canvas->GetPixels()),
                    m_width,
                    m_height,
                    32,
                    0
                );
            }
        }
    }
}
