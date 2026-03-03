#pragma once

#include <memory>
#include <Rendering/Window.h>
#include <Rendering/Renderer.h>
#include <Rendering/Camera.h>
#include <Rendering/Config.h>
#include <Rendering/Primitive.h>
#include <Input/Input.h>
#include <Util/Time.h>
#include <Util/Light.h>
#include <World/Level.h>
#include <World/Wall.h>

namespace Engine
{
    class App
    {
    public:
        App();
        virtual ~App();

        void Run();
        void Quit();

    protected:
        virtual void Update();
        virtual void Render();

        [[nodiscard]] Rendering::Renderer* GetRenderer() const { return m_renderer.get(); }
        [[nodiscard]] Rendering::Window* GetWindow() const { return m_window.get(); }
        [[nodiscard]] Rendering::Camera* GetCamera() const { return m_camera.get(); }
        [[nodiscard]] Util::Time* GetTime() const { return m_time.get(); }
        [[nodiscard]] Util::Light* GetLight() const { return m_light.get(); }
        [[nodiscard]] World::Level* GetLevel() const { return m_level.get(); }

    private:
        std::unique_ptr<Rendering::Window> m_window;
        std::unique_ptr<Rendering::Renderer> m_renderer;
        std::unique_ptr<Rendering::Camera> m_camera;
        std::unique_ptr<Util::Time> m_time;
        std::unique_ptr<Util::Light> m_light;
        std::unique_ptr<World::Level> m_level;

        bool m_isRunning;
    };

    App* CreateApp();
}
