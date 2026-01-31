#include "CloseStgGraphics.h"
#include <OpenStgCore.h>
#include <OpenStgDefine.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

BOOL_T OG_API OgGpInit()
{

    {
        OG_CR_PROGRAM_MODULE pm;
        memset((void *)&pm, 0, sizeof(OG_CR_PROGRAM_MODULE));
        const char** rgszDependency= (const char**)OgCrNoExceptPtr(OgCrSetErrorIfValueIsNULL(calloc(1,sizeof(const char*)),OgCrMakeError(OPEN_STG_NAMESPACE_CORE,OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR)));
        rgszDependency[0] = OPEN_STG_REGISTRAR_NAME_CORE;
        pm.iSize = sizeof(OG_CR_PROGRAM_MODULE);
        pm.ufModuleRegisteredFlag = OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE;
        pm.pszModuleDisplayName = "Graphics - Display";
        pm.pszModuleRegisteredName = OPEN_STG_REGISTRAR_NAME_GRAPHICS;
        pm.pfFormatErrorMessage = &OgGpFormatErrorMessage;
        pm.pfDestoryProgramModule = &OgGpQuit;
        pm.pvAdditionalData = NULL;
        pm.rgpszDependenciesRegisteredName = rgszDependency;
        pm.uCountOfDependencies = 1;
        pm.uModuleNamespace = OPEN_STG_NAMESPACE_SDL3;
        if(!OgCrRegisterProgramModule(&pm,NULL))
        {
            return FALSE;
        }
    }
    if(!OgCrSetErrorIfValueIsFalse(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_CAMERA | SDL_INIT_EVENTS |SDL_INIT_GAMEPAD | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC),OgCrMakeError(OPEN_STG_NAMESPACE_SDL3, OPEN_STG_ERROR_MESSAGE_SDL3_INIT_FAILED)))
    {
        return FALSE;
    }
    return TRUE;
}
void OG_API OgGpQuit()
{
    SDL_Quit();
}