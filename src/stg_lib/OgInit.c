#include "CloseStg.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

BOOL_T OgInit(uint64_t ufInitFlag)
{
    if (!OgCrInit())
    {
        fprintf_s(stderr, "全体目光向我看齐，我说个事，我是个傻逼！");
        _Exit(EXIT_FAILURE);
    }
    // if (!ghInitSDL())
    // {
    //     return FALSE;
    // }
    return (TRUE);
}
// BOOL_T ghInitSDL()
// {
//     {
//         OG_CR_PROGRAM_MODULE pm;
//         pm.iSize = sizeof(OG_CR_PROGRAM_MODULE);
//         pm.ufModuleRegisteredFlag = OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE;
//         pm.pszModuleDisplayName = "Graph";
//         pm.pszModuleRegisteredName = "ice_thorn.sdl3.cirno";
//         pm.pfFormatErrorMessage = &OgSdlFormatErrorMessage;
//         pm.pvAdditionalData = NULL;
//         pm.rgpszDependencyRegistraredName = NULL;
//         pm.uCountOfDependencies = 0;
//         pm.uModuleNamespace = OPEN_STG_NAMESPACE_SDL3;
//         if (OgCrRegisterProgramModule(&pm, NULL))
//         {
//             return FALSE;
//         }
//     }
//     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD | SDL_INIT_JOYSTICK))
//         goto setSdlErrorAndReturn;
//     if (TTF_Init())
//         goto setSdlErrorAndReturn;
//     return OG_TRUE;
// setSdlErrorAndReturn:
//     SET_ERROR_AND_MESSAGE(OgCrMakeError(OPEN_STG_NAMESPACE_SDL3, OPEN_STG_ERROR_MESSAGE_SDL3_INIT_FAILED),
//                           SDL_GetError());
//     return OG_FALSE;
// }
