#include "OpenStg/CloseStgCore.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
BOOL_T OG_API OgCrInit()
{
    if (!ogCrPvInitTSL())
    {
        char szErrorString[64];
        strerror_s(szErrorString, sizeof(szErrorString), errno);
        fprintf_s(stderr, "%s\n", szErrorString);
        _Exit(EXIT_FAILURE);
    }
    if (!ogCrPvInitProgramStaticVariables())
        return FALSE;
    if (!ogCrPvInitModuleRegistrar())
        return FALSE;

    OG_CR_PROGRAM_MODULE pm;
    memset((void *)&pm, 0, sizeof(sizeof(OG_CR_PROGRAM_MODULE)));
    pm.iSize = sizeof(OG_CR_PROGRAM_MODULE);
    pm.ufModuleRegisteredFlag = OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE;
    pm.pszModuleDisplayName = "Core";
    pm.pszModuleRegisteredName = OPEN_STG_REGISTRAR_NAME_CORE;
    pm.pvAdditionalData = malloc(sizeof(OG_CR_PV_CORE_MODULE_ADDITIONAL_DATA));
    if (pm.pvAdditionalData == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_MEMORY_ERROR));
        return FALSE;
    }
    memset(pm.pvAdditionalData, 0, sizeof(OG_CR_PV_CORE_MODULE_ADDITIONAL_DATA));
    pm.fnDestoryProgramModule = NULL;
    pm.fnFormatErrorMessage = &OgCrFormatErrorMessage;
    pm.fnPostInitalzationFunction = NULL;
    pm.fnFreeFunc = &free;
    pm.rgpszDependenciesRegisteredName = NULL;
    pm.uCountOfDependencies = 0;
    pm.uModuleNamespace = OPEN_STG_NAMESPACE_CORE;
    OgCrNoExceptBoolean(OgCrRegisterProgramModule(&pm, NULL));

    return TRUE;
}
