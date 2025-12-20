#include "CloseStg.h"
#include <stdlib.h>
#include <string.h>

OG_BOOL OgRegisteredProgramModule(const OG_PROGRAM_MODULE_PUBLIC *pModule)
{
    if (pModule == NULL)
    {
        setError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return FALSE;
    }
    OG_PROGRAM_DATA *ppd = getProgramData();
    OG_PROGRAM_MODULE_PUBLIC *ppm = NULL;
    size_t sDisplay = 0, sRegistered = 0, sSturct = sizeof(OG_PROGRAM_MODULE_PUBLIC);
    char *pszDisplay = NULL, *pszRegistered = NULL;
    OG_BOOL bIsStatic = FALSE, bMakeRegisteredNameAsDisplayName = FALSE;
    bIsStatic = pModule->ufModuleRegisteredFlag & OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE;
    uint32_t uIndex;
    // 这里必须先分配内存再分配模块
    if (pModule->pszModuleDisplayName)
    {
        sDisplay = strlen(pModule->pszModuleDisplayName) + 1;
    }
    else
    {
        sDisplay = strlen(pModule->pszModuleRegisteredName) + 1;
        bMakeRegisteredNameAsDisplayName = TRUE;
    }
    sRegistered = strlen(pModule->pszModuleRegisteredName) + 1;
    // NOTE: 这里的'或'不是短路的！！
    if ((pszDisplay = (char *)malloc(sDisplay)) == NULL | (pszRegistered = (char *)malloc(sRegistered)) == NULL)
    {
        setError(OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR);
        goto freeResources;
    }
    memset((void *)pszDisplay, 0, sDisplay);
    memset((void *)pszRegistered, 0, sRegistered);
    // 终于分配完了

    if (!allocModule(&ppm, (bIsStatic) ? pModule->uModuleNamespace : -1, &uIndex))
    {
        goto freeResources;
    }
    // 复制成员
    ppm->iSize = -1;
    ppm->pszModuleDisplayName = pszDisplay;
    strcpy_s(pszDisplay, sDisplay,
             (bMakeRegisteredNameAsDisplayName) ? /*true:*/ pModule->pszModuleRegisteredName
                                                : /*false:*/ pModule->pszModuleDisplayName);
    ppm->pszModuleRegisteredName = pszRegistered;
    strcpy_s(pszRegistered, sRegistered, pModule->pszModuleRegisteredName);
    ppm->pvAdditionalData = pModule->pvAdditionalData;
    ppm->ufModuleRegisteredFlag = pModule->ufModuleRegisteredFlag;
    ppm->uModuleNamespace = uIndex;
    return TRUE;
freeResources:
    free(pszDisplay);
    free(pszRegistered);
    return FALSE;
}