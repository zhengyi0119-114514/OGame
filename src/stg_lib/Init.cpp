#ifdef WIN32
// Windows https://learn.microsoft.com/en-us/windows/win32/winsock/using-winsock
#include <winsock2.h>
#else
// Mac Or Linux
#include <sys/socket.h>
#endif
#include "open_game.hpp"
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdint>
#include <string>

#ifdef LIBSAFEC
#include <safec.h>
#endif // LIBSAFEC
namespace open_stg
{
std::string InitOG_h(bool &bOk)
{
    bOk = true;
    std::string message{};
#ifdef WIN32
    WSADATA wsaData{};
    int iResult{};
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult)
    {
        message = "WinSock Init fail";
        goto end;
    }
#endif

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        message += SDL_GetError();
        goto end;
    }
    if (TTF_Init() != 0)
    {
        message += TTF_GetError();
        goto end;
    }
    if (uint32_t flag = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP; IMG_Init(flag) != flag)
    {
        message += IMG_GetError();
        goto end;
    }
    if (uint32_t flag = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG | MIX_INIT_OPUS | MIX_INIT_WAVPACK | MIX_INIT_MP3;
        Mix_Init(flag) != flag)
    {
        message += Mix_GetError();
        goto end;
    }
    return message;
end:
    bOk = false;
    return std::move(message);
}
} // namespace open_stg
