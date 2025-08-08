#include <spdlog/spdlog.h>
#ifdef WIN32
// Windows https://learn.microsoft.com/en-us/windows/win32/winsock/using-winsock
#include <winsock2.h>
#else
// Mac Or Linux
#include <sys/socket.h>
#if defined LINUX || defined linux
#include "unistd.h"
#endif
#endif

#if __has_include("safec.h")
#include <safec.h>
#endif

#include "og.hpp"
#include <SDL3/SDL.h>

namespace open_stg
{
void InitOpenGame()
{
    try
    {
        ::open_stg::sdl3_h::InitSdlModule();
    }
    catch(const error_h::InitException& e)
    {
        SPDLOG_ERROR(e.what());
        throw;
    }
}
void QuitOpenGame()
{
    ::open_stg::sdl3_h::QuitSdlModule();
}
} // namespace open_stg
