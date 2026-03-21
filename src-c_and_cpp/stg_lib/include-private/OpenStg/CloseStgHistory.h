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
#define OPEN_STG_FLAG_PRIVATE_PROGRAM_MODULE_MODULE_USED UINT64_C(0x0000000000000001)
    typedef struct TagOgCrPvPROGRAM_MODULE
    {
        OG_MODULE_REGISTERED_FLAG_T ufFlag;
        char szDisplayName[OPEN_STG_CONST_MAX_NAME_LENGTH];
        char szRegisteredName[OPEN_STG_CONST_MAX_NAME_LENGTH];
        OG_CR_FORMAT_ERROR_MESSAGE_FUNCTION_T fnFormatErrorMessage;
        OG_CR_DESTORY_PROGRAM_MODULE_T fnDestoryProgramModule;
        OG_CR_INITALZATION_FUNCTION_T fnPostInitalzationFunction;
        void *pvAdditionalData;
        OG_CR_MODULE_ADDITIONAL_RELEASE_FUNCTION_T fnFreeFunc;
        uint32_t *rgDependencies;
        size_t uCountOfDependencies;
        OG_MODULE_NAMESPACE_T uModuleNamespace;
    } OG_CR_PV_PROGRAM_MODULE;
    typedef struct TagOgCrPvCORE_MODULE_ADDITIONAL_DATA
    {
        intptr_t iPlaceholder;
    } OG_CR_PV_CORE_MODULE_ADDITIONAL_DATA;
#if OPEN_STG_MACRO_USE_LIBDWARF
    typedef struct TagOgCrPvDBG_INFO
    {
        void *dbg; // 实际上是 Dwarf_Debug
        char szFilePath[];
    } OG_CR_PV_DBG_INFO;
#endif
    typedef struct TagOgCrPvPROGRAM_STATIC_VARIABLES
    {
#if OPEN_STG_MACRO_USE_LIBDWARF
        /**
         * @brief libdwarf的 Dwarf_Debug
         */
        void *rgpDbg;
#endif
        /**
         * @brief 模块注册器局部变量，成员是OG_CR_PV_PROGRAM_MODULE
         */
        OG_CR_UNIVERSAL_REGISTRAR *urModuleRegistrar;
        OG_CR_EXCEPTION_HANDLER_FUNCTION_T rgfnExceptionHandlers[OPEN_STG_CONST_MAX_EXCEPTION_HANDLER_FUNCTION];
        void *pvModuleContainer;
    } OG_CR_PV_PROGRAM_STATIC_VARIABLES;
#if defined __cplusplus
}
#endif
#endif
