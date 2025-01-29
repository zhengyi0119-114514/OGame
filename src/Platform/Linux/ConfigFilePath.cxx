#include "Modules/Config.hpp"
#include <cstdlib>
#include <filesystem>
namespace OGame::Config
{
std::filesystem::path GetConfigFileDirectory()
{
    auto homePath = getenv("HOME");
    auto result = std::filesystem::path{homePath} / ".config" / "ogame";
    return result;
}
} // namespace OGame::Config