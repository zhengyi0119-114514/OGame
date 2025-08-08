#include"og_opt_h.hpp"
#include <filesystem>
#include <windows.h>
namespace fs = std::filesystem;

namespace open_stg::opt_h
{
std::filesystem::path get_program_option_path()
{
    SIZE_T sBuferSize = MAX_PATH*sizeof(WCHAR);
    WCHAR* buffer = (WCHAR*)HeapAlloc(GetProcessHeap(),0,sBuferSize);
    if (buffer == nullptr)
    {
        throw std::bad_alloc{};
    }
    ZeroMemory((void*)buffer,sBuferSize);
    const WCHAR* fStr {LR"sb(%LOCALAPPDATA%\ogame)sb"};
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