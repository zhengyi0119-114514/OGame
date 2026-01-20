#include "CloseStg.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

OG_PRIVATE OG_CR_UNIVERSAL_REGISTRAR *s_urModuleRegistrar = NULL;
void OG_CDECL freeProgramModule(void *pvModule)
{
    OG_CR_PV_PROGRAM_MODULE *ppm = (OG_CR_PV_PROGRAM_MODULE *)pvModule;
    free((void *)ppm->pszDisplayName);
    ppm->pszDisplayName = NULL;
    free((void *)ppm->pszRegisteredName);
    ppm->pszRegisteredName = NULL;
}
BOOL_T OG_CDECL crInitModuleRegistrar(void)
{
    OG_CR_UNIVERSAL_REGISTRAR_INFORMATION uri;
    uri.iSize = sizeof(OG_CR_UNIVERSAL_REGISTRAR_INFORMATION);
    uri.pfDestoryMemberFunction = &freeProgramModule;
    uri.pszStructureName = NULL;
    uri.uItemStructureSize = sizeof(OG_CR_PV_PROGRAM_MODULE);
    uri.uPreAllocatedCount = 3;
    if ((s_urModuleRegistrar = OgCrCreateUniversalRegistrar(&uri)) == NULL)
    {
        return FALSE;
    }
    return TRUE;
}
void OgFormatErrorMessage(OG_ERROR_T eError, char *pszBuffer, uint64_t uLengthOfBuffer)
{
    if (pszBuffer == NULL)
        return;
    OG_CR_PV_PROGRAM_MODULE *ppm =
        (OG_CR_PV_PROGRAM_MODULE *)OgCrUniversalRegistrarGetItem(s_urModuleRegistrar, OgCrGetErrorNamesoace(eError));
    if (ppm->pfFormatErrorMessage != NULL)
    {
        ppm->pfFormatErrorMessage(OgCrGetErrorCode(eError), pszBuffer, uLengthOfBuffer);
    }
}
BOOL_T OG_CDECL OgCrRegisterProgramModule(const OG_CR_PROGRAM_MODULE *mod, uint32_t *puNamespaceOutput)
{
    if (mod == NULL || mod->pszModuleRegisteredName == NULL)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return FALSE;
    }
    int64_t iItemIndex;
    OG_CR_PV_PROGRAM_MODULE *ppm;
    if ((mod->ufModuleRegisteredFlag & OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE) != 0)
    {
        if ((iItemIndex = OgCrUniversalRegistrarAllocatePreallocatedItem(s_urModuleRegistrar, mod->uModuleNamespace,
                                                                         (void **)&ppm)) < 0)
        {
            return FALSE;
        }
    }
    else
    {
        if ((iItemIndex = OgCrUniversalRegistrarAllocateItem(s_urModuleRegistrar, (void **)&ppm)) < 0)
        {
            return FALSE;
        }
    }
    OG_MODULE_NAMESPACE_T uModuleNamespace = (uint32_t)iItemIndex;
    char *pszRegisteredName = NULL, *pszDisplayName = NULL;
    const char*pszDispalyNameSource = NULL;
    size_t sCountOfRegisteredName = strlen(mod->pszModuleRegisteredName) + 1,sCountOfDisplayName = 0;
    if (mod->pszModuleDisplayName == NULL)
    {
        pszDispalyNameSource = mod->pszModuleRegisteredName;
    }
    else
    {
        pszDispalyNameSource = mod->pszModuleDisplayName;
    }
    sCountOfDisplayName = strlen(pszDispalyNameSource) + 1;
    if ((pszDisplayName = (char*)malloc(sCountOfDisplayName)) == NULL || 
        (pszRegisteredName = (char*)malloc(sCountOfRegisteredName)) == NULL)
    {
        free((void*)pszDisplayName);
        free((void *)pszRegisteredName);
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR);
        return FALSE;
    }
    strcpy_s(pszDisplayName, sCountOfDisplayName, pszDispalyNameSource);
    strcpy_s(pszRegisteredName, sCountOfRegisteredName, mod->pszModuleRegisteredName);
    ppm->pszDisplayName = pszDisplayName;
    ppm->pszRegisteredName = pszRegisteredName;
    ppm->pfFormatErrorMessage = mod->pfFormatErrorMessage;
    // FIXME: 创建新的模块索引
    ppm->ufPermissions = 0;
    ppm->uModuleNamespace = uModuleNamespace;
    if (puNamespaceOutput != NULL)
        *puNamespaceOutput = uModuleNamespace;
    return TRUE;
}
BOOL_T OG_CDECL crDestroyModuleRegistrar(void)
{
    OgCrDestoryUniversalRegistrar(s_urModuleRegistrar);
    return TRUE;
}
typedef struct TagOgCrMODULE_ITREATOR
{
    OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri;
} OG_CR_MODULE_ITERATOR;
OG_CR_MODULE_ITERATOR *OG_CDECL OgCrCreateModuleRegistrarIterator()
{
    OG_CR_MODULE_ITERATOR *pmi = (OG_CR_MODULE_ITERATOR *)malloc(sizeof(OG_CR_MODULE_ITERATOR));
    if (pmi == NULL)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR);
        return NULL;
    }
    pmi->puri = OgCrCreateUniversalRegistrarIterator(s_urModuleRegistrar);
    if (pmi->puri == NULL)
    {
        free(pmi);
        return NULL;
    }
    return pmi;
}
BOOL_T OG_CDECL OgCrModuleRegistrarIteratorNext(OG_CR_MODULE_ITERATOR *piter, OG_CR_PROGRAM_MODULE *pmod)
{
    if (piter == NULL || pmod == NULL)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return FALSE;
    }
    OG_CR_PV_PROGRAM_MODULE *ppvmod = NULL;
    while ((ppvmod = (OG_CR_PV_PROGRAM_MODULE *)OgCrUniversalRegistrarIteratorNext(piter->puri)) != NULL)
    {
        pmod->ufModuleRegisteredFlag = ppvmod->ufFlag;
        pmod->pszModuleDisplayName = ppvmod->pszDisplayName;
        pmod->pszModuleRegisteredName = ppvmod->pszRegisteredName;
        pmod->pfFormatErrorMessage = ppvmod->pfFormatErrorMessage;
        pmod->rgpszDependencyRegistraredName = NULL;
        pmod->uCountOfDependencies = 0;
        pmod->uModuleNamespace = ppvmod->uModuleNamespace;
    }
    return TRUE;
}
void OG_CDECL OgCrDestoryModuleRegistrarIterator(OG_CR_MODULE_ITERATOR *piter)
{
    if (piter == NULL)
    {
        return;
    }
    OgCrDestoryUniversalRegistrarIterator(piter->puri);
    free((void *)piter);
}
BOOL_T OG_CDECL OgCrUnregisterProgramModule(const char* pszModuleRegisteredName)
{
    OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri = NULL;
    OG_CR_PV_PROGRAM_MODULE *pm = NULL;
    if ((puri = OgCrCreateUniversalRegistrarIterator(s_urModuleRegistrar)) == NULL)
    {
        return FALSE;
    }
    while ((pm = (OG_CR_PV_PROGRAM_MODULE*)OgCrUniversalRegistrarIteratorNext(puri)) != NULL)
    {
        if (strcmp(pm->pszRegisteredName, pszModuleRegisteredName) == 0)
        {
            if (OgCrUniversalRegistrarFreeItem(s_urModuleRegistrar, pm->uModuleNamespace))
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }
    return FALSE;
}