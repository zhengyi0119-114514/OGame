#include "Modules/Config.hpp"
#include <cstdlib>
#include <filesystem>
#include <format>
#include <spdlog/spdlog.h>
namespace OGame::Config
{
std::filesystem::path GetConfigFileDirectory()
{
    auto homePath = getenv("HOME");
    spdlog::info(std::format("Home path : {:}", homePath));
    auto result = std::filesystem::path{homePath} / ".config" / "ogame";
    return result;
}
} // namespace OGame::Config