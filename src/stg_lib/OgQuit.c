#include "CloseStg.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

OG_INTERNAL BOOL_T OG_CDECL crFreeTSL();
BOOL_T crQ___SDL()
{
    SDL_Quit();
    TTF_Quit();
    return OG_TRUE;
}

BOOL_T OgQuit()
{
    BOOL_T bResult = OG_TRUE;
    bResult &= crDestroyModuleRegistrar();
    bResult &= crQ___SDL();
    bResult &= crFreeTSL();
    return bResult;
}