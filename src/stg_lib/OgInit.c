#include "CloseStg.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>

OG_BOOL_T OgInit(uint64_t ufInitFlag)
{
    OG_BOOL_T bResult = TRUE;
    if (!inilTSL(0))
    {
        fputs(strerror(errno), stderr);
        _Exit(EXIT_FAILURE);
    }
    if (!initProgramData(3))
    {
        return FALSE;
    }
    OG_ERRNO = 114514;
    if (!initSDL())
    {
        return FALSE;
    }
    {
        OG_PROGRAM_MODULE_PUBLIC mod;
        mod.iSize = sizeof(OG_PROGRAM_MODULE_PUBLIC);
        mod.pszModuleDisplayName = "OpenStg Core";
        mod.pszModuleRegisteredName = "ice_thorn.core.cirno";
        mod.pfGetErrorMessage = OgCrGetErrorMessage;
        mod.pvAdditionalData = NULL;
        mod.ufModuleRegisteredFlag = OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE;
        mod.uModuleNamespace = OPEN_STG_NAMESPACE_CORE;
        if (!OgRegisteredProgramModule(&mod))
        {
            return FALSE;
        }
    }
    reserveModule(1);
    return bResult;
}
OG_BOOL_T initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD | SDL_INIT_JOYSTICK))
        goto setSdlErrorAndReturn;
    if (TTF_Init())
        goto setSdlErrorAndReturn;
    {
        OG_PROGRAM_MODULE_PUBLIC mod;
        mod.iSize = sizeof(OG_PROGRAM_MODULE_PUBLIC);
        mod.pszModuleDisplayName = "OpenStg SDL3";
        mod.pszModuleRegisteredName = "ice_thorn.sdl3.chiruno";
        mod.pfGetErrorMessage = OgSdlGetErrorMessage;
        mod.pvAdditionalData = NULL;
        mod.ufModuleRegisteredFlag = OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE;
        mod.uModuleNamespace = OPEN_STG_NAMESPACE_CORE;
        if (OgRegisteredProgramModule(&mod))
        {
            return FALSE;
        }
    }
    return OG_TRUE;
setSdlErrorAndReturn:
    SET_ERROR_AND_MESSAGE(OgMakeError(OPEN_STG_NAMESPACE_SDL3,OPEN_STG_ERROR_MESSAGE_SDL3_INIT_FAILED),SDL_GetError());
    return OG_FALSE;
}