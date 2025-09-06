#include <spdlog/spdlog.h>
#ifdef WIN32
// Windows https://learn.microsoft.com/en-us/windows/win32/winsock/using-winsock
#include <winsock2.h>
#else
// Mac Or Linux
#include <sys/socket.h>
#if defined unix || defined POSIX
#include "unistd.h"
#endif
#endif

#if __has_include("safec.h")
#include <safec.h>
#endif

#if __has_include("unistd.h")
#include <unistd.h>
#endif

#include "og.hpp"
#include <SDL3/SDL.h>

namespace OpenGame
{
void InitOpenGame()
{
    try
    {
        ::OpenGame::sdl3_h::InitSdlModule();
    }
    catch (const error_h::InitException &e)
    {
        SPDLOG_ERROR(e.what());
        throw;
    }
#ifdef POSIX
    uid_t uUserId = geteuid();
    if (uUserId == 0)
    {
        throw error_h::RunAsRootAtException{};
    }
#endif
}
void QuitOpenGame()
{
    ::OpenGame::sdl3_h::QuitSdlModule();
}
} // namespace OpenGame
