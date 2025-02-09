#pragma once
#include "Resource.hh"
#include <cstdint>
#include <filesystem>
namespace OGame::Config
{
const std::filesystem::path WindowConfigFile{OGame::Resources::ConfigFileDirectory / "Window.cfg"};
using WINDOW_CONFIG = struct
{
    uint32_t WindowWidth;
    uint32_t WindowHeight;
};
void InitWindowConfig();
std::filesystem::path GetConfigFileDirectory();
void CreateDirectoryIfNotExists(std::filesystem::path p);

const WINDOW_CONFIG& WindowConfig();
} // namespace OGame::Config
