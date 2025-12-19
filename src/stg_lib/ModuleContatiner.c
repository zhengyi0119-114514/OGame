#include "CloseStg.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

OG_BOOL initModuleContainer(uint32_t uCount)
{
    OG_PROGRAM_DATA *ppd = getProgramData();
    ppd->rgModules = (OG_RPOGRAM_MODULE_PRIVATE *)calloc(uCount, sizeof(OG_RPOGRAM_MODULE_PRIVATE));
    if (ppd->rgModules == NULL)
    {
        setError(OG_ERROR_MESSAGE_NO_ERROR);
        return OG_FALSE;
    }
    return OG_TRUE;
}
OG_BOOL reserveModule(uint32_t uCount)
{
    OG_PROGRAM_DATA *ppd = getProgramData();
    OG_RPOGRAM_MODULE_PRIVATE *rgModules = NULL;
    size_t uCountOfReserved = ppd->uCountOfReserved + uCount;
    size_t sNewModuleIndex = ppd->uCountOfReserved;
    rgModules = (OG_RPOGRAM_MODULE_PRIVATE *)realloc((void *)ppd->rgModules,
                                                     sizeof(OG_RPOGRAM_MODULE_PRIVATE) * uCountOfReserved);
    if (rgModules == NULL)
    {
        setError(OG_ERROR_MESSAGE_MEMORY_ERROR);
        return FALSE;
    }
    memset((void *)rgModules + sNewModuleIndex, 0, sizeof(OG_RPOGRAM_MODULE_PRIVATE) * uCount);
    ppd->rgModules = rgModules;
    ppd->uCountOfReserved += uCount;
    return TRUE;
}
OG_BOOL allocModule(OG_PROGRAM_MODULE_PUBLIC **ppModule, int64_t sPreAllocIndex, uint32_t *puOutIndex)
{
    OG_PROGRAM_DATA *ppd = getProgramData();
    OG_RPOGRAM_MODULE_PRIVATE *pModule = NULL;
    // 检查模块空间名称是否是静态分配
    if (sPreAllocIndex >= 0)
    {
        if (ppd->uCountOfReserved > sPreAllocIndex + 1) // 检查大小
        {
            if (!reserveModule(sPreAllocIndex + 1 - ppd->uCountOfReserved)) // 大小不足，分配内存
                return FALSE;
        }
        if (ppd->rgModules[sPreAllocIndex].bIsUsed) // 模块已被占用
        {
            setError(OG_ERROR_MESSAGE_MODULE_EXIST);
            return FALSE;
        }
        else
        {
            pModule = ppd->rgModules + sPreAllocIndex;
            pModule->bIsUsed = TRUE; // 占用模块
            *ppModule = &(pModule->pmModule);
            if (!puOutIndex)
                *puOutIndex = sPreAllocIndex;
            return TRUE;
        }
    }
    else
    {
        for (size_t sIndex = 0, sEnd = ppd->uCountOfReserved; sIndex < sEnd; ++sIndex)
        {
            pModule = ppd->rgModules + sIndex;
            if (!pModule->bIsUsed)
            {
                pModule->bIsUsed = TRUE;
                *ppModule = &pModule->pmModule;
                if (!puOutIndex)
                    *puOutIndex = ppd->uCountOfReserved - 1;
                return TRUE;
            }
        }
        if (!reserveModule(1))
        {
            return FALSE;
        }
        if (!puOutIndex)
            *puOutIndex = ppd->uCountOfReserved - 1;
        pModule = ppd->rgModules + ppd->uCountOfReserved - 1;
        *ppModule = &pModule->pmModule;
        pModule->bIsUsed = TRUE;
        return TRUE;
    }
}
OG_BOOL freeModuleContainer()
{
    // FIXME: 释放数据成员
    OG_PROGRAM_DATA *ppd = getProgramData();
    OG_RPOGRAM_MODULE_PRIVATE *rgModules = ppd->rgModules;
    for (size_t sIndex = 0, sMax = ppd->uCountOfReserved; sIndex < sMax; ++sIndex)
    {
        free((void *)rgModules[sIndex].pmModule.pszModuleDisplayName);
        free((void *)rgModules[sIndex].pmModule.pszModuleRegisteredName);
    }
    free(rgModules);
    return TRUE;
}