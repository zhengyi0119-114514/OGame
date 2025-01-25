#include "Modules/Config.hpp"
#include <cstdlib>
#include <filesystem>
#include <format>
#include <spdlog/spdlog.h>
namespace OGame::Config
{
std::filesystem::path GetConfigFilePath()
{
    auto homePath = getenv("HOME");
    spdlog::info(std::format("Home path : {:}", homePath));
    auto result = std::filesystem::path{homePath} / ".config" / "ogame" / "config.txt";
    CreateDirectoryIfNotExists(result);
    return result;
}
} // namespace OGame::Config