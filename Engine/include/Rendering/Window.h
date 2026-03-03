#pragma once

#include <X11/Xlib.h>
#include <Config.h>

namespace Engine::Rendering
{
    class Window
    {
    public:
        Window();
        ~Window();

        void Clear() const;
        void SwapBuffers() const;

        [[nodiscard]] Display* GetDisplay() const { return m_display; }
        [[nodiscard]] ::Window GetWindow() const { return m_window; }
        [[nodiscard]] bool IsRunning() const { return m_isRunning; }
        [[nodiscard]] int GetWidth() const;
        [[nodiscard]] int GetHeight() const;

        bool PollEvents();

    private:
        void Cleanup();

        Display* m_display;
        ::Window m_window;
        int m_screen;
        Atom m_wmDeleteMessage;
        bool m_isRunning;
    };
}
