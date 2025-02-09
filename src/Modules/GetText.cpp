#include "Modules/Text.hxx"
#include <cassert>
#include <format>
#include <libconfig.hh>
#include <spdlog/spdlog.h>

namespace lcfg = libconfig;
namespace OGame::Resources::Text
{
static TEXT_RESOURCE s_TextResource;
const TEXT_RESOURCE &GetText()
{
    return s_TextResource;
}
void InitText()
{
    s_TextResource = {};
    libconfig::Config cfgFile{};
    try
    {
        cfgFile.readFile(TextFile.string().c_str());
    }
    catch (const lcfg::FileIOException &e)
    {
        SPDLOG_ERROR(std::format("File io exception {:}", e.what()));
        throw;
    }
    catch (const lcfg::ParseException &e)
    {
        SPDLOG_ERROR(std::format("Parse exception at {:} - {:}", e.getFile(), e.getError()));
        throw;
    }
    try
    {
        s_TextResource.Title = cfgFile.lookup("Title").c_str();
    }
    catch (const lcfg::SettingNotFoundException &e)
    {
        SPDLOG_ERROR(std::format("Setting {:} not found.", e.getPath()));
        throw;
    }
}
} // namespace OGame::Resources::Text
