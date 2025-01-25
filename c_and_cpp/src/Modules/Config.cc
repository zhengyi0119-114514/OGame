#include "Modules/Config.hpp"
#include <filesystem>
#include <format>
#include <spdlog/spdlog.h>

namespace OGame::Config
{
void CreateDirectoryIfNotExists(std::filesystem::path path)
{
    auto dirPath = path.parent_path();
    if(!std::filesystem::exists(dirPath))
    {

        std::filesystem::create_directory(dirPath);
        SPDLOG_INFO(std::format("Create directory : {:}",dirPath.string()));
    }
}
} // namespace OGame::Config