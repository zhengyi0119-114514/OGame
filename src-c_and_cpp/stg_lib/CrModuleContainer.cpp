#include "OpenStg/CloseStgCore.h"
#include <OpenStg/OpenStgCorePP.hh>
#include <concepts>
#include <math.h>
#include <numbers>
#include <ranges>
#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

template <typename T>
OG_ALWAYS_INLINE OG_PRIVATE inline T *AllocArrayAndInitalize(size_t sNumber, size_t sUnit = sizeof(T))
{
    return static_cast<T *>(calloc(sNumber, sUnit));
}
template <typename T> OG_ALWAYS_INLINE OG_PRIVATE inline T *AllocMemoryAndInitalize(size_t sSize = sizeof(T))
{
    auto *p = static_cast<T *>(malloc(sSize));
    if (p != nullptr)
    {
        memset(static_cast<void *>(p), 0, sSize);
    }
    return p;
}
OG_PRIVATE void OG_API ogCrPvFreeProgramModule(OG_CR_PV_PROGRAM_MODULE *pMod)
{
    if (pMod == nullptr)
        { return; }
    if ((pMod->ufFlag & OPEN_STG_FLAG_PRIVATE_PROGRAM_MODULE_MODULE_USED) == 0)
    {
        return;
    }
    if (pMod->fnFreeFunc != nullptr)
    {
        pMod->fnFreeFunc(pMod->pvAdditionalData);
    }
    if (pMod->fnDestoryProgramModule != nullptr)
    {
        pMod->fnDestoryProgramModule();
    }
}

using OG_PV_MODULE_HANDLE_T = uint32_t;
OG_PRIVATE OG_ALWAYS_INLINE constexpr inline uint16_t ogCrPvGetHandleLevel(OG_PV_MODULE_HANDLE_T h)
{
    return static_cast<uint16_t>((h >> 16) & UINT32_C(0x0000ffff));
}
OG_PRIVATE OG_ALWAYS_INLINE constexpr inline uint16_t ogCrPvGetHandleIndexInLevel(OG_PV_MODULE_HANDLE_T h)
{
    return static_cast<uint16_t>(h & UINT32_C(0x0000ffff));
}
OG_PRIVATE OG_ALWAYS_INLINE constexpr inline OG_PV_MODULE_HANDLE_T ogCrPvMakeHandle(uint16_t uLevel, uint16_t uIndex)
{
    return static_cast<OG_PV_MODULE_HANDLE_T>(uLevel) << 16 | static_cast<OG_PV_MODULE_HANDLE_T>(uIndex);
}

OG_PRIVATE OG_ALWAYS_INLINE inline BOOL_T ogCrPvIsModuleUsed(const OG_CR_PV_PROGRAM_MODULE &m)
{
    return (m.ufFlag & OPEN_STG_FLAG_PRIVATE_PROGRAM_MODULE_MODULE_USED) != 0;
}
struct ModuleContainer
{
};
BOOL_T OG_API ogCrPvInitModuleRegistrar(void)
{
    return FALSE;
}
OG_CR_PV_PROGRAM_MODULE *ogCrPvGetProgramModuleFormHandle(OG_PV_MODULE_HANDLE_T h)
{
    return NULL;
}
void OgFormatErrorMessage(OG_ERROR_T eError, char *pszBuffer, uint64_t uLengthOfBuffer)
{
}
BOOL_T OG_API OgCrRegisterProgramModule(const OG_CR_PROGRAM_MODULE *pModule, uint32_t *puNamespaceOutput)
{
    return FALSE;
}
BOOL_T OG_API ogCrDestroyModuleRegistrar(void)
{
    delete static_cast<ModuleContainer *>(ogCrPvGetProgramStaticVariables()->pvModuleContainer);
    ogCrPvGetProgramStaticVariables()->pvModuleContainer = nullptr;
    return TRUE;
}
typedef struct TagOgCrPROGRAM_MODULE_ITREATOR
{
} OG_CR_PROGRAM_MODULE_ITERATOR;
OG_CR_PROGRAM_MODULE_ITERATOR *OG_API OgCrCreateProgramModuleRegistrarIterator()
{
    return NULL;
}
BOOL_T OG_API OgCrProgramModuleRegistrarIteratorNext(OG_CR_PROGRAM_MODULE_ITERATOR *pIterator,
                                                     OG_CR_PROGRAM_MODULE *pModule)
{
    return TRUE;
}
void OG_API OgCrDestoryProgramModuleRegistrarIterator(OG_CR_PROGRAM_MODULE_ITERATOR *piter)
{
}
BOOL_T OG_API OgCrUnregisterProgramModule(PROGRAM_MODULE_HANDLE pModule)
{
    return TRUE;
}
PROGRAM_MODULE_HANDLE OG_API OgCrGetProgramModulePointerByNamespace(OG_MODULE_NAMESPACE_T uNamespace)
{
    return NULL;
}
PROGRAM_MODULE_HANDLE OG_API OgCrGetProgramModulePointerByRegistrerdName(const char *pszRegisteredName)
{
    return NULL;
}
void *OG_API OgCrGetProgramModuleAdditionalData(PROGRAM_MODULE_HANDLE h)
{
    return NULL;
}
