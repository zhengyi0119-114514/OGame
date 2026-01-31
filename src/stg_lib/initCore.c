#include "CloseStgCore.h"
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
    if (!ogCrPvInitModuleRegistrar())
        goto enterTextHere;
    {
        OG_CR_PROGRAM_MODULE pm;
        pm.iSize = sizeof(OG_CR_PROGRAM_MODULE);
        pm.ufModuleRegisteredFlag = OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE;
        pm.pszModuleDisplayName = "Core";
        pm.pszModuleRegisteredName = OPEN_STG_REGISTRAR_NAME_CORE;
        pm.pvAdditionalData = NULL;
        pm.pfDestoryProgramModule = NULL;
        pm.pfFormatErrorMessage = &OgCrFormatErrorMessage;
        pm.pfFreeFunc = &free;
        pm.rgpszDependenciesRegisteredName = NULL;
        pm.uCountOfDependencies = 0;
        pm.uModuleNamespace = OPEN_STG_NAMESPACE_CORE;
        OgCrNoExceptBoolean(OgCrRegisterProgramModule(&pm, NULL));
    }
    return TRUE;
enterTextHere: {
    OgCrFormatErrorMessage(OgCrGetErrorCode(OG_ERRNO), OG_CHAR_BUFFER,
                           OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH);
    fprintf_s(stderr, "%s\n", OG_CHAR_BUFFER);
    return FALSE;
}
}
