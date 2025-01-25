#define OGAME_EXPORT
#include <Windows.h>
#include "Modules/Config.hpp"
static bool bConfigFileExist = false;
namespace OGame::Config
{
    std::filesystem::path GetConfigFilePath()
    {
        size_t sStrSize = sizeof(wchar_t)*MAX_PATH;
        wchar_t * pStrPath = (wchar_t*)malloc(sStrSize);
        memset((void*)pStrPath,0,sStrSize);
        ExpandEnvironmentStringsW(L"%LOCALAPPDATA%\\OGame\\Cnfig.txt",pStrPath,(WORD)sStrSize);
        std::filesystem::path pResult{pStrPath};
        free((void*)pStrPath);
        return pResult;
    }
} // namespace ogame::config