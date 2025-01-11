#define ogame_export
#include "log4cplus/log4cplus.h"
#include "modules.h"
#include <SDL2/SDL.h>

ogame_api_private static bool bIsInit = false;
ogame_api OGAME_RESULT OGameInit(OGame_GameInfo *pInfo)
{
    if (!bIsInit)
    {
        bIsInit = true;
        log4cplus::Initializer();
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
        log4cplus::BasicConfigurator config;
        config.configure();
    }
    if (pInfo == null)
    {
        return OGAME_ERROR_ARGUEMENT_IS_NULL;
    }
    var *pLogger = new log4cplus::Logger;
    (*pLogger) = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Main Logger"));
    pInfo->pLogger = (void *)pLogger;
    LOG4CPLUS_INFO((*pLogger), "OGame Init");
    return OGAME_ERROR_NO_ERROR;
}
ogame_api OGAME_RESULT OGameFreeGameInfo(OGame_GameInfo *pInfo)
{
    if (pInfo == null)
    {
        return OGAME_ERROR_ARGUEMENT_IS_NULL;
    }
    delete (log4cplus::Logger *)pInfo->pLogger;
    pInfo->pLogger = null;
    return OGAME_ERROR_NO_ERROR;
}