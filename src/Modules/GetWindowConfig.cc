#include "Errors.hpp"
#include "Modules/Config.hpp"
#include <SDL_video.h>
#include <filesystem>
#include <format>
#include <spdlog/spdlog.h>
#include <toml.hpp>
#include <toml11/parser.hpp>
namespace OGame::Config
{
void GetWindowConfig(WINDOW_CONFIG &out)
{
    std::filesystem::path dateFilePath = std::filesystem::current_path() / "data" / "WindowConfig.toml";
    std::filesystem::path filePath = GetConfigFileDirectory() / "WindowConfig.toml";
#ifdef _DEBUG
    if(std::filesystem::exists(filePath))
    {
        std::filesystem::remove(filePath);
        SPDLOG_INFO(std::format("Remove {:}",filePath.string()));
    }
    std::filesystem::copy_file(dateFilePath, filePath);
    SPDLOG_INFO(std::format("Copy file \"{:}\" to \"{:}\"", dateFilePath.string(), filePath.string()));
#else
    if (!std::filesystem::exists(filePath))
    {
        std::filesystem::copy_file(dateFilePath, filePath);
        SPDLOG_INFO(std::format("Copy file form {:} to {:}", dateFilePath.string(), filePath.string()));
    }
#endif
    if (!std::filesystem::exists(filePath))
    {
        throw OGame::Errors::FileNotFoundException{filePath};
    }
    auto tomlDoc = toml::parse(filePath.string().c_str());

    if (tomlDoc.contains("WindowHeigt"))
    {
        out.WindowHeight = tomlDoc["WindowHeigt"].as_integer();
    }
    if (tomlDoc.contains("WindowWidth"))
    {
        out.WindowWidth = tomlDoc["WindowWidth"].as_integer();
    }
    if (tomlDoc.contains("WindowTitle"))
    {
        out.WindowTitle = tomlDoc["WindowTitle"].as_string();
    }
    if (tomlDoc.contains("WindowUseVulkan"))
    {
        if (tomlDoc["WindowUseVulkan"].as_boolean())
        {
            out.WindowFlag |= SDL_WINDOW_VULKAN;
        }
    }
    if (tomlDoc.contains("WindowUseOpenGL"))
    {
        if (tomlDoc["WindowUseOpenGL"].as_boolean())
        {
            out.WindowFlag |= SDL_WINDOW_OPENGL;
        }
    }
    if (tomlDoc.contains("WindowAllocHeightDPI"))
    {
        if (tomlDoc["WindowAllocHeightDPI"].as_boolean())
        {
            out.WindowFlag |= SDL_WINDOW_ALLOW_HIGHDPI;
        }
    }
}
} // namespace OGame::Config