#include "define.h"
#include <stdint.h>
#ifndef OGAME_MODULES
#define OGAME_MODULES 1
#include "modules/math.h"
typedef struct
{
    void* pLogger;
    struct
    {
        void* pPlatformInfo;
        uint32_t iPlatformID;
    };
}OGame_AppInfo;
typedef OGame_AppInfo* OGame_pAppInfo;
typedef const OGame_AppInfo* OGame_pcAppInfo;
/**
 * @brief Init the game
 * 
 * @param pInfo 
 * @return OGAME_RESULT 
 */
ogame_api OGAME_RESULT OGame_Init(OGame_pAppInfo pInfo);
ogame_api OGAME_RESULT OGame_PlatformInit(OGame_pcAppInfo pInfo);
#endif // endof OGame/Modules.h