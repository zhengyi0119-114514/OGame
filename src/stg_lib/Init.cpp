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

std::string InitOG(bool& bOk)
{
    bOk = true;
    std::string message{};
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
    if (uint32_t flag = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG | MIX_INIT_OPUS | MIX_INIT_WAVPACK | MIX_INIT_MP3 ;Mix_Init(flag) != flag)
    {
        message += Mix_GetError();
        goto end;
    }
    return message;
end:
    bOk = false;
    return std::move(message);
}
