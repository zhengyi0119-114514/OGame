#define OGAME_EXPORT
#include "modules/Config.hpp"
#include <Windows.h>
static bool bConfigFileExist = false;
namespace ogame::config
{
    std::filesystem::path OGAME_API GetConfigFilePath()
    {
        size_t sStrSize = sizeof(wchar_t)*MAX_PATH;
        wchar_t * pStrPath = (wchar_t*)malloc(sStrSize);
        memset((void*)pStrPath,0,sStrSize);
        ExpandEnvironmentStringsW(L"%LOCALAPPDATA%\\OGame\\Cnfig.toml",pStrPath,(WORD)sStrSize);
        std::filesystem::path pResult{pStrPath};
        free((void*)pStrPath);
        return pResult;
    }
} // namespace ogame::config