#include "Modules/Config.hpp"
#include <SDL_video.h>
#include <cstdint>
#include <cstring>
#include <format>
#include <libconfig.h++>
#include <libconfig.hh>
#include <spdlog/spdlog.h>
namespace lcfg = libconfig;
namespace OGame::Config
{
static WINDOW_CONFIG s_WindowConfig;
void InitWindowConfig()
{
    s_WindowConfig = WINDOW_CONFIG{};
    lcfg::Config windowCfgFile{};
    try
    {
        windowCfgFile.readFile(WindowConfigFile.string());
    }
    catch (const lcfg::FileIOException& e)
    {
        SPDLOG_ERROR(std::format("File io excepthion ,{:}",WindowConfigFile.string()));
        throw;
    }
    catch (const lcfg::ParseException& e)
    {
        SPDLOG_ERROR(std::format("Parse exception at {:} - {:}", e.getFile(), e.getError()));
        throw;
    }
    try
    {
        uint32_t width = windowCfgFile.lookup("Width");
        s_WindowConfig.WindowWidth = width;
        uint32_t height = windowCfgFile.lookup("Height");
        s_WindowConfig.WindowHeight = height;
    }
    catch (lcfg::SettingNotFoundException e)
    {
        SPDLOG_ERROR(std::format("Setting '{:}' not found.", e.getPath()));
    }
}
const WINDOW_CONFIG &WindowConfig()
{
    return s_WindowConfig;
}
} // namespace OGame::Config