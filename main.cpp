#include <Engine/Core.h>

namespace Game
{
    class App final : public Engine::App
    {
    public:
        App()
        {
            // Configure window defaults
            Engine::Window::SetWindowTitle("ENGINE _f"); Engine::Window::SetDefaultWindowX(1200);
            Engine::Window::SetDefaultWindowY(800); Engine::Window::SetDesiredFPS(144);

            // Configure camera
            GetCamera()->SetPosition({ -50.0f, 0.0f, 400.0f }); GetCamera()->SetAngleX(360.0f);

            // Configure / initialize light
            GetLight()->SetPosition({ 300.0f, -100.0f, 200.0f }); GetLight()->SetDirection({ 0.3f, 1.0f, 0.5f });
            GetLight()->SetColor(0xFFFFFF); GetLight()->SetIntensity(1.0f); GetLight()->SetIsDirectional(false);

            // Load level
            if (const auto level = Engine::World::Level::LoadFromFile("level.txt"))
            {
                // Transfer walls to level
                for (const auto& wall : level->GetWalls())
                {
                    auto newWall = std::make_unique<Engine::World::Wall>(
                        wall->GetPosition(),
                        wall->GetWidth(),
                        wall->GetHeight(),
                        wall->GetAngle(),
                        wall->GetType(),
                        wall->GetColor(),
                        wall->GetFlipCulling()
                    );
                    GetLevel()->AddWall(std::move(newWall));
                }
            }

            std::cout << "[Game] Initialized" << std::endl;
        }

        void Update() override
        {
            float dt = static_cast<float>(GetTime()->GetDeltaSeconds());
            float moveSpeed = Engine::GetMovementSpeed() * dt;
            float rotateSpeed = Engine::GetRotationSpeed() * dt;

            // Camera rotation
            if (Engine::Input::IsKeyDown(Engine::Input::Key::Left)) GetCamera()->RotateX(-rotateSpeed);
            if (Engine::Input::IsKeyDown(Engine::Input::Key::Right)) GetCamera()->RotateX(rotateSpeed);
            if (Engine::Input::IsKeyDown(Engine::Input::Key::Up)) GetCamera()->RotateY(-rotateSpeed);
            if (Engine::Input::IsKeyDown(Engine::Input::Key::Down)) GetCamera()->RotateY(rotateSpeed);

            // Camera movement
            if (Engine::Input::IsKeyDown(Engine::Input::Key::W)) GetCamera()->MoveForward(moveSpeed);
            if (Engine::Input::IsKeyDown(Engine::Input::Key::S)) GetCamera()->MoveForward(-moveSpeed);
            if (Engine::Input::IsKeyDown(Engine::Input::Key::A)) GetCamera()->MoveRight(-moveSpeed);
            if (Engine::Input::IsKeyDown(Engine::Input::Key::D)) GetCamera()->MoveRight(moveSpeed);
            if (Engine::Input::IsKeyDown(Engine::Input::Key::Space)) GetCamera()->MoveUp(-moveSpeed);
            if (Engine::Input::IsKeyDown(Engine::Input::Key::LeftShift)) GetCamera()->MoveUp(moveSpeed);

            // Toggle features
            if (Engine::Input::IsKeyPressed(Engine::Input::Key::L)) Engine::Rendering::SetEnableLighting(!Engine::Rendering::GetEnableLighting());
            if (Engine::Input::IsKeyPressed(Engine::Input::Key::F)) Engine::Rendering::SetEnableFog(!Engine::Rendering::GetEnableFog());

            // Save level
            if (Engine::Input::IsKeyPressed(Engine::Input::Key::S) && 
                Engine::Input::IsKeyDown(Engine::Input::Key::LeftControl)) 
                GetLevel()->SaveToFile("level.txt");
        }

        void Render() override
        {
            // Clear buffers
            GetRenderer()->GetCanvas()->Clear(Engine::Rendering::GetFogColor());
            GetRenderer()->GetCanvas()->ClearDepth();

            // Draw floor
            Engine::Rendering::Primitive::DrawFloor(
                GetRenderer()->GetCanvas(),
                100, 100,
                100.0f,
                100.0f,
                0xFFaaefbb,
                0xFF78de99,
                *GetLight(),
                *GetCamera()
            );

            // Draw level
            GetLevel()->Render(GetRenderer()->GetCanvas(), *GetLight(), *GetCamera());

            // Present to screen
            GetRenderer()->Present(GetRenderer()->GetCanvas());
        }
    };
}

Engine::App* Engine::CreateApp()
{
    HELLOENGINE();
    return new Game::App();
}
