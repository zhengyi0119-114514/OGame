#include "CloseStg.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

OG_BOOL_T initModuleContainer(uint32_t uCount)
{
    OG_PROGRAM_DATA_T *ppm = getProgramData();
    ppm->rgModules = (OG_PROGRAM_MODULE_PRIVATE *)calloc(uCount, sizeof(OG_PROGRAM_MODULE_PRIVATE));
    ppm->uCountOfReserved = uCount;
    if (ppm->rgModules == NULL)
    {
        setError(OPEN_STG_ERROR_MESSAGE_NO_ERROR);
        return OG_FALSE;
    }
    return OG_TRUE;
}
OG_BOOL_T reserveModule(uint32_t uCount)
{
    OG_PROGRAM_DATA_T *ppd = getProgramData();
    OG_PROGRAM_MODULE_PRIVATE *rgModules = NULL;
    size_t uCountOfReserved = ppd->uCountOfReserved + uCount;
    size_t sNewModuleIndex = ppd->uCountOfReserved;
    rgModules = (OG_PROGRAM_MODULE_PRIVATE *)realloc((void *)ppd->rgModules,
                                                     sizeof(OG_PROGRAM_MODULE_PRIVATE) * uCountOfReserved);
    if (rgModules == NULL)
    {
        setError(OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR);
        return FALSE;
    }
    // 注意操作优先级!!!
    memset((void *)(rgModules + sNewModuleIndex), 0, sizeof(OG_PROGRAM_MODULE_PRIVATE) * uCount);
    ppd->rgModules = rgModules;
    ppd->uCountOfReserved += uCount;
    return TRUE;
}
OG_BOOL_T allocModule(OG_PROGRAM_MODULE_PUBLIC **ppModule, int64_t sPreAllocIndex, uint32_t *puOutIndex)
{
    OG_PROGRAM_DATA_T *ppd = getProgramData();
    OG_PROGRAM_MODULE_PRIVATE *pTargetPrivateModule = NULL;
    uint32_t uMaxIndex = ppd->uCountOfReserved - 1, uTargetIndex;
    // 检查参数
    if (ppModule == NULL)
        goto invalidParameter;
    if (puOutIndex == NULL)
        goto invalidParameter;
    if (sPreAllocIndex >= 0) // Index是预分配的
    {
        if (sPreAllocIndex > uMaxIndex)
        {
            if (!reserveModule(sPreAllocIndex - uMaxIndex))
            {
                return FALSE;
            }
        }
        if (ppd->rgModules[sPreAllocIndex].bIsUsed)
        {
            setError(OPEN_STG_ERROR_MESSAGE_MODULE_EXIST);
            
            return FALSE;
        }
        else
        {
            pTargetPrivateModule = &ppd->rgModules[sPreAllocIndex];
            uTargetIndex = sPreAllocIndex;
        }
    }
    else
    {
        for (uint32_t uIndex = 0, uMax = ppd->uCountOfReserved; uIndex < uMax; ++uIndex)
        {
            OG_PROGRAM_MODULE_PRIVATE *pppm = &ppd->rgModules[uIndex];
            if (pppm->bIsUsed)
            {
                continue;
            }
            else
            {
                pTargetPrivateModule = pppm;
                uTargetIndex = uIndex;
                break;
            }
        }
        if (pTargetPrivateModule == NULL)
        {
            if (!reserveModule(1))
            {
                return FALSE;
            }
            uTargetIndex = uMaxIndex + 1;
            pTargetPrivateModule = &ppd->rgModules[uTargetIndex];
        }
    }

    *puOutIndex = uTargetIndex;
    *ppModule = &pTargetPrivateModule->pmModule;
    return TRUE;
invalidParameter:
    setError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
    return FALSE;
}

OG_BOOL_T freeModuleContainer()
{
    OG_PROGRAM_DATA_T *ppd = getProgramData();
    OG_PROGRAM_MODULE_PRIVATE *rgModules = ppd->rgModules;
    for (size_t sIndex = 0, sMax = ppd->uCountOfReserved; sIndex < sMax; ++sIndex)
    {
        free((void *)rgModules[sIndex].pmModule.pszModuleDisplayName);
        free((void *)rgModules[sIndex].pmModule.pszModuleRegisteredName);
    }
    free(rgModules);
    return TRUE;
}