#include "CloseStg.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

OG_EXTERN OG_CDECL OG_BOOL quitTSL();
OG_BOOL quitSDL()
{
    SDL_Quit();
    TTF_Quit();
    return OG_TRUE;
}

OG_BOOL OgQuit()
{
    OG_BOOL bResult = OG_TRUE;
    bResult &= quitSDL();
    bResult &= quitTSL();
    bResult &= freeProgramData();
    return bResult;
}