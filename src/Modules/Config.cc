#include "Modules/Config.hpp"
#include <filesystem>
#include <format>
#include <spdlog/spdlog.h>

namespace OGame::Config
{
void CreateDirectoryIfNotExists(std::filesystem::path path)
{
    if(!std::filesystem::exists(path))
    {
        std::filesystem::create_directory(path);
        SPDLOG_INFO(std::format("Create directory : {:}",path.string()));
    }
}
} // namespace OGame::Config