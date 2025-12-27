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
    typedef struct OgTagPublicPROGRAM_MODULE
    {
        int64_t iSize;
        const char *pszModuleDisplayName;
        union {
            const char *pszModuleRegisteredName;
            const char *pszModuleRegisteredId;
            intptr_t iPlaceholder;
        };
        OG_FORMAT_ERROR_MESSAGE_FUNCTION_T pfGetErrorMessage;
        void *pvAdditionalData;
        OG_MODULE_REGISTERED_FLAG_T ufModuleRegisteredFlag;
        OG_ERROR_NAMESPACE_T uModuleNamespace;
    } OG_PROGRAM_MODULE_PUBLIC_VER1;
    typedef OG_PROGRAM_MODULE_PUBLIC_VER1 OG_PROGRAM_MODULE_PUBLIC;

    typedef struct OgTagPrivatePROGRAM_MODULE
    {
        OG_PROGRAM_MODULE_PUBLIC_VER1 pmModule;
        OG_BOOL_T bIsUsed;
    } OG_PROGRAM_MODULE_PRIVATE;
#if defined __cplusplus
}
#endif
#endif