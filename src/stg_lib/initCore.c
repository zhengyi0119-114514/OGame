#include "CloseStg.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined WIN32
#endif
BOOL_T OG_CDECL OgCrInit()
{
    if (!crInitTSL(0))
    {
        char szErrorString[64];
        strerror_s(szErrorString,sizeof(szErrorString),errno);
        fprintf_s(stderr, "%s\n", szErrorString);
        _Exit(EXIT_FAILURE);
    }
    if (!crInitModuleRegistrar())
        goto enterTextHere;
    {
        OG_CR_PROGRAM_MODULE pm;
        pm.iSize = sizeof(OG_CR_PROGRAM_MODULE);
        pm.ufModuleRegisteredFlag = OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE;
        pm.pszModuleDisplayName = "Core";
        pm.pszModuleRegisteredName = "ice_thorn.core.cirno";
        pm.pvAdditionalData = NULL;
        pm.rgpszDependencyRegistraredName = NULL;
        pm.uCountOfDependencies = 0;
        pm.uModuleNamespace = OPEN_STG_NAMESPACE_CORE;
        if (!OgCrRegisterProgramModule(&pm, NULL))
            goto enterTextHere;
    }
    return TRUE;
enterTextHere: {
    OgCrFormatErrorMessage(OG_ERRNO, OG_ERROR_MESSAGE, OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH);
    fprintf_s(stderr, "%s", OG_ERROR_MESSAGE);
    _Exit(EXIT_FAILURE);
}
}
