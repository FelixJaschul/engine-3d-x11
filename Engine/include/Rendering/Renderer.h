#pragma once

#include <Rendering/Window.h>
#include <Rendering/Canvas.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <memory>

namespace Engine::Rendering
{
    class Renderer
    {
    public:
        explicit Renderer(Window* window);
        ~Renderer();

        void SetColor(unsigned long color) const;
        void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, unsigned long color) const;
        void DrawRect(int x, int y, int width, int height, unsigned long color) const;
        void DrawText(int x, int y, const char* text, unsigned long color) const;
        void Clear() const;
        void Present() const;

        void Present(Canvas* canvas);

        [[nodiscard]] Canvas* GetCanvas() const { return m_canvas.get(); }

        void OnResize(int width, int height);

    private:
        Display* m_display;
        ::Window m_window;
        int m_screen;
        XImage* m_image;
        GC m_gc;
        std::unique_ptr<Canvas> m_canvas;
        int m_width;
        int m_height;
    };
}
