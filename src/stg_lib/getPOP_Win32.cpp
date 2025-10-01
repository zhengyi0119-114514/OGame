#include"og_opt_h.hpp"
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

namespace OpenGame::Option
{
std::filesystem::path GetProgramOptionFileDirectory()
{
    SIZE_T sBuferSize = MAX_PATH*sizeof(WCHAR);
    WCHAR* buffer = (WCHAR*)HeapAlloc(GetProcessHeap(),0,sBuferSize);
    if (buffer == nullptr)
    {
        throw std::bad_alloc{};
    }
    ZeroMemory((void*)buffer,sBuferSize);
    const WCHAR* fStr {LR"baka(%LOCALAPPDATA%\ogame)baka"};
    ExpandEnvironmentStrings(fStr,buffer,MAX_PATH -1);
    std::filesystem::path path{buffer};
    HeapFree(GetProcessHeap(),0,(void*)buffer);
    if(!fs::exists(path))
    {
        fs::create_directory(path);
    }
    return path;
}
}