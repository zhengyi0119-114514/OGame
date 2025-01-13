#define ogame_export
#include "log4cplus/log4cplus.h"
#include "modules.h"
#include <SDL2/SDL.h>

ogame_api_private static bool s_bIsInit = false;
ogame_api_private static log4cplus::Logger * s_pLonger;
static auto  OGameInitLogger()
{
    log4cplus::initialize();
    log4cplus::BasicConfigurator config;
    config.configure();
    return new log4cplus::Logger();
}
static void SDL2Init()
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_AUDIO);
}
ogame_api OGAME_RESULT OGame_Init(OGame_pAppInfo pInfo)
{
    if(!s_bIsInit)
    {
        SDL2Init();
        s_pLonger =  OGameInitLogger();
        if(s_pLonger == null)
        {
            return OGAME_ERROR_INIT_FAILD ;
        }
        s_bIsInit = true;
    }
    if(pInfo == null)
    {
        return OGAME_ERROR_ARGUEMENT_IS_NULL;
    }
    else
    {
        pInfo->pLogger = (void*)s_pLonger;
    }
    return OGAME_ERROR_NO_ERROR;
}