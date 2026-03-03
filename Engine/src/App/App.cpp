#include <App/App.h>
#include <iostream>
#include <Input/Input.h>
#include <memory>
#include <thread>
#include <chrono>

namespace Engine
{
    App::App()
        : m_isRunning(false)
    {
        m_window = std::make_unique<Rendering::Window>();
        m_renderer = std::make_unique<Rendering::Renderer>(m_window.get());
        m_camera = std::make_unique<Rendering::Camera>();
        m_time = std::make_unique<Util::Time>();
        m_light = std::make_unique<Util::Light>();
        m_level = std::make_unique<World::Level>();

        std::cout << "[Engine] Creating Application..." << std::endl;
    }

    App::~App()
    {
        std::cout << "[Engine] Destroying Application..." << std::endl;
    }

    void App::Run()
    {
        m_isRunning = true;

        while (m_isRunning)
        {
            auto frameStart = std::chrono::steady_clock::now();

            if (!m_window->PollEvents()) m_isRunning = false;

            m_time->Update();
            Update();
            Input::UpdateFrame();

            Render();

            auto frameEnd = std::chrono::steady_clock::now();
            std::chrono::duration<double> frameTime = frameEnd - frameStart;

            double targetFrameTime = 1.0 / Engine::Window::GetDesiredFPS();
            if (frameTime.count() < targetFrameTime)
            {
                std::chrono::duration<double> sleepDuration = std::chrono::duration<double>(targetFrameTime) - frameTime;
                std::this_thread::sleep_for(sleepDuration);
            }
        }
    }

    void App::Quit()
    {
        m_isRunning = false;
    }

    void App::Update()
    {
        // Override in subclass
    }

    void App::Render()
    {
        // Override in subclass
    }
}
