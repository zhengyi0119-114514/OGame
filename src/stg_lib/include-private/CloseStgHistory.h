#include <OpenStgDefine.h>
#include <stdint.h>

#if !defined OPEN_GAME_PRIVATE_HISTORY_H
#define OPEN_GAME_PRIVATE_HISTORY_H 1

#if defined __cplusplus
extern "C"
{
#endif
    typedef struct
    {
        int64_t iSize;

    } OgStructWithSizeParameter;
    typedef struct TagOgCrPvPROGRAM_MODULE
    {
        OG_MODULE_REGISTERED_FLAG_T ufFlag;
        const char *pszDisplayName;
        const char *pszRegisteredName;
        OG_CR_FORMAT_ERROR_MESSAGE_FUNCTION_T pfFormatErrorMessage;
        OG_CR_DESTORY_PROGRAM_MODULE_T pfDestoryProgramModule;
        void *pvAdditionalData;
        OG_CR_MODULE_ADDITIONAL_RELEASE_FUNCTION_T pfFreeFunc;
        struct TagOgCrPvPROGRAM_MODULE **rgDependencies;
        uint32_t uCountOfDependencies;
        uint32_t uGeneration;
        uint64_t ufPermissions;
        OG_MODULE_NAMESPACE_T uModuleNamespace;
    } OG_CR_PV_PROGRAM_MODULE;
#if defined __cplusplus
}
#endif
#endif
