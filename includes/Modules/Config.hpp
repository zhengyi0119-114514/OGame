#pragma once
#include <cstdint>
#include <filesystem>
namespace OGame::Config
{
using WINDOW_CONFIG = struct
{
    uint32_t WindowWidth;
    uint32_t WindowHeight;
    uint32_t WindowFlag;
    std::string WindowTitle;
};
std::filesystem::path GetConfigFileDirectory();
void CreateDirectoryIfNotExists(std::filesystem::path path);
void GetWindowConfig(WINDOW_CONFIG& out);
} // namespace OGame::Config
