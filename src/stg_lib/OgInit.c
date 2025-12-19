#include "CloseStg.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>

OG_BOOL OgInit(uint64_t ufInitFlag)
{
    OG_BOOL bResult = TRUE;
    if (!inilTSL(0))
    {
        fputs(strerror(errno), stderr);
        _Exit(EXIT_FAILURE);
    }
    if (!initProgramData(3))
    {
        return FALSE;
    }
    return bResult;
}
OG_BOOL initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD | SDL_INIT_JOYSTICK))
        goto setSdlErrorAndReturn;
    if (TTF_Init())
        goto setSdlErrorAndReturn;

    return OG_TRUE;
setSdlErrorAndReturn:
    OG_ERRNO = OG_MAKE_ERROR(OG_ERROR_NAMESPACE_SDL3, OG_ERROR_MESSAGE_SDL3_INIT_FAILED);
    OG_ERROR_MESSAGE = SDL_GetError();
    return OG_FALSE;
}