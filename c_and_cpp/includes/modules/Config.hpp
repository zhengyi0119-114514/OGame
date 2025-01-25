#pragma once
#include <filesystem>
#pragma once
namespace OGame::Config
{
    std::filesystem::path GetConfigFilePath();
    void CreateDirectoryIfNotExists(std::filesystem::path path);
}