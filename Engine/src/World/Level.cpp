#include <World/Level.h>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <ios>
#include <sstream>
#include <utility> 

namespace Engine::World
{
    Level::Level()
    {
    }

    void Level::AddWall(std::unique_ptr<Wall> wall)
    {
        m_walls.push_back(std::move(wall));
    }

    void Level::Clear()
    {
        m_walls.clear();
    }

    std::unique_ptr<Level> Level::LoadFromFile(const std::string& filename)
    {
        auto level = std::make_unique<Level>();
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "[Level] Failed to open file: " << filename << std::endl;
            return level;
        }

        std::string line;
        int lineNum = 0;

        while (std::getline(file, line))
        {
            lineNum++;

            // Skip empty lines and comments
            if (line.empty() || line[0] == '#' || line[0] == '\n') continue;

            std::istringstream iss(line);

            Math::Vec::Vec3 pos;
            float width, height, angle;
            std::string typeStr;
            uint32_t color = 0xFFCCCCCC;
            int flipCulling = 0;

            iss >> pos.x >> pos.y >> pos.z >> width >> height >> angle >> typeStr;

            if (iss >> std::hex >> color)
            {
                iss >> std::dec >> flipCulling;
            }

            WallType type = WallType::Floor;
            if (typeStr == "WALL_X" || typeStr == "WALLX")
                type = WallType::WallX;
            else if (typeStr == "WALL_Z" || typeStr == "WALLZ")
                type = WallType::WallZ;
            else if (typeStr == "FLOOR")
                type = WallType::Floor;

            auto wall = std::make_unique<Wall>(pos, width, height, angle, type, color, flipCulling != 0);
            level->AddWall(std::move(wall));
        }

        file.close();
        std::cout << "[Level] Loaded " << level->GetWallCount() << " walls from " << filename << std::endl;

        return level;
    }

    void Level::SaveToFile(const std::string& filename) const
    {
        std::ofstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "[Level] Failed to save file: " << filename << std::endl;
            return;
        }

        for (const auto& wall : m_walls)
        {
            const char* typeStr = "FLOOR";
            if (wall->GetType() == WallType::WallX)
                typeStr = "WALL_X";
            else if (wall->GetType() == WallType::WallZ)
                typeStr = "WALL_Z";

            auto pos = wall->GetPosition();
            file << pos.x << " " << pos.y << " " << pos.z << " "
                 << wall->GetWidth() << " " << wall->GetHeight() << " "
                 << wall->GetAngle() << " " << typeStr << " "
                 << std::hex << std::uppercase << wall->GetColor() << std::dec << " "
                 << (wall->GetFlipCulling() ? 1 : 0) << "\n";
        }

        file.close();
        std::cout << "[Level] Saved " << m_walls.size() << " walls to " << filename << std::endl;
    }

    void Level::Render(Rendering::Canvas* canvas, const Util::Light& light, const Rendering::Camera& camera) const
    {
        for (const auto& wall : m_walls)
        {
            wall->Render(canvas, light, camera);
        }
    }
}
