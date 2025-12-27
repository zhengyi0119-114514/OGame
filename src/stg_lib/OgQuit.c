#include "CloseStg.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

OG_EXTERN OG_BOOL_T OG_CDECL  quitTSL();
OG_BOOL_T quitSDL()
{
    SDL_Quit();
    TTF_Quit();
    return OG_TRUE;
}

OG_BOOL_T OgQuit()
{
    OG_BOOL_T bResult = OG_TRUE;
    bResult &= quitSDL();
    bResult &= quitTSL();
    bResult &= freeProgramData();
    return bResult;
}