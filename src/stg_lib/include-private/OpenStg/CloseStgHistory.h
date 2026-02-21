#include <OpenStg/OpenStgDefine.h>
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
        OG_CR_FORMAT_ERROR_MESSAGE_FUNCTION_T fnFormatErrorMessage;
        OG_CR_DESTORY_PROGRAM_MODULE_T fnDestoryProgramModule;
        OG_CR_INITALZATION_FUNCTION_T fnPostInitalzationFunction;
        void *pvAdditionalData;
        OG_CR_MODULE_ADDITIONAL_RELEASE_FUNCTION_T fnFreeFunc;
        struct TagOgCrPvPROGRAM_MODULE **rgDependencies;
        uint32_t uCountOfDependencies;
        uint32_t uGeneration;
        uint64_t ufPermissions;
        OG_MODULE_NAMESPACE_T uModuleNamespace;
    } OG_CR_PV_PROGRAM_MODULE;
    typedef struct TagOgCrPvCORE_MODULE_ADDITIONAL_DATA
    {
        intptr_t iPlaceholder;
    } OG_CR_PV_CORE_MODULE_ADDITIONAL_DATA;
    typedef struct TagOgCrPvPROGRAM_STATIC_VARIABLES
    {
        /**
         * @brief 模块注册器局部变量，成员是OG_CR_PV_PROGRAM_MODULE
         */
        OG_CR_UNIVERSAL_REGISTRAR *urModuleRegistrar;
        OG_CR_EXCEPTION_HANDLER_FUNCTION_T rgfnExceptionHandlers[OPEN_STG_CONST_MAX_EXCEPTION_HANDLER_FUNCTION];
    } OG_CR_PV_PROGRAM_STATIC_VARIABLES;
#if defined __cplusplus
}
#endif
#endif
