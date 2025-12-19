#include <OpenStgDefine.h>
#include <stdint.h>

#if !defined OPEN_GAME_PRIVATE_HISTORY_H
#define OPEN_GAME_PRIVATE_HISTORY_H 1
#if defined WIN32 || defined WINNT || defined _WIN32
#define OG_EXPORT __declspec(dllexport)
#define OG_CDECL __cdecl
#define OG_STDCALL __stdcall
#define OG_INTERNAL
#else
#define OG_EXPORT
#define OG_CDECL __attribute__((__cdecl__))
#define OG_INTERNAL __attribute__((visibility("hidden")))
#endif
#define OG_PRIVATE static
#define OG_EXTERN extern

#if defined __cplusplus
extern "C"
{
#endif
    typedef struct
    {
        int64_t iSize;

    } OgStructWithSizeParameter;
    typedef void (*OG_CDECL OgGetErrorMessageFunction)(OG_ERROR_CODE code, char *pszBuffer, uint64_t uLengthOfBuffer);
    typedef struct OgTagPublicPROGRAM_MODULE
    {
        int64_t iSize;
        const char *pszModuleDisplayName;
        union {
            const char *pszModuleRegisteredName;
            const char *pszModuleRegisteredId;
            intptr_t iPlaceholder;
        };
        OgGetErrorMessageFunction pfGetErrorMessage;
        void *pvAdditionalData;
        ModuleRegisteredFlag ufModuleRegisteredFlag;
        uint32_t uModuleNamespace;
    } OG_PROGRAM_MODULE_PUBLIC_VER1;
    typedef OG_PROGRAM_MODULE_PUBLIC_VER1 OG_PROGRAM_MODULE_PUBLIC;

    typedef struct OgTagPrivatePROGRAM_MODULE
    {
        OG_PROGRAM_MODULE_PUBLIC_VER1 pmModule;
        OG_BOOL bIsUsed;
    } OG_RPOGRAM_MODULE_PRIVATE;
#if defined __cplusplus
}
#endif
#endif