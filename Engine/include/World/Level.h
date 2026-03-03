#pragma once

#include <World/Wall.h>
#include <memory>
#include <string>
#include <vector>

namespace Engine::World
{
    class Level
    {
    public:
        Level();
        ~Level() = default;

        void AddWall(std::unique_ptr<Wall> wall);
        void Clear();

        static std::unique_ptr<Level> LoadFromFile(const std::string& filename);
        void SaveToFile(const std::string& filename) const;

        void Render(Rendering::Canvas* canvas, const Util::Light& light,
                   const Rendering::Camera& camera) const;

        [[nodiscard]] size_t GetWallCount() const { return m_walls.size(); }
        [[nodiscard]] const std::vector<std::unique_ptr<Wall>>& GetWalls() const { return m_walls; }

    private:
        std::vector<std::unique_ptr<Wall>> m_walls;
    };
}