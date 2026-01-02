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
    typedef struct TagCrPROGRAM_MODULE
    {
        int64_t iSize; ///< (REQUIRED)版本控制，总应该初始化为sizeof(OG_CR_PROGRAM_MODULE)
        OG_MODULE_REGISTERED_FLAG_T ufModuleRegisteredFlag; ///< 输入，位志符
        const char *pszModuleDisplayName; ///< 输入，模块显示名称，如果为NULL，则会被设置为 pszRegisteredName
        union {
            const char *pszModuleRegisteredName; ///< (REQUIRED)输入，注册名称，必须是唯一的，等同与 pszRegisteredId
            const char *pszModuleRegisteredId;   ///< 注册ID，必须是唯一的，等同与 pszRegisteredName
            intptr_t iPlaceholder;               ///< 这个字段为什么会有用？😄
        };
        OG_FORMAT_ERROR_MESSAGE_FUNCTION_T pfFormatErrorMessage; ///< (REQUIRED)输入，获取错误码对应的字符串描述函数
        void *pvAdditionalData;                               ///< 模块额外信息
        const char **rgpszDependencyRegistraredName;          ///< 输入，指向一个字符串数组，包涵依赖项的注册名
        uint32_t uCountOfDependencies;                        ///< 输入，指示rgpszDependencyRegistraredName成员的个数
        OG_MODULE_NAMESPACE_T uModuleNamespace;               ///< 输入，设置为模块空间名称
    } OG_CR_PROGRAM_MODULE;
    typedef struct TagCrPvPROGRAM_MODULE
    {
        OG_MODULE_REGISTERED_FLAG_T ufFlag;
        const char *pszDisplayName;
        const char *pszRegisteredName;
        OG_FORMAT_ERROR_MESSAGE_FUNCTION_T pfFormatErrorMessage;
        struct TagCrPvPROGRAM_MODULE **rgDependencies;
        uint32_t uCountOfDependencies;
        uint64_t ufPermissions;
        OG_MODULE_NAMESPACE_T uModuleNamespace;
    } OG_CR_PV_PROGRAM_MODULE;
    typedef struct TagUNIVERSAL_REGISTRAR_INFORMATION
    {
        int64_t iSize;
        OG_CR_UNIVERSAL_REGISTRAR_FLAG_T ufCreateFlags;
        uint32_t uItemStructureSize;
        uint32_t uPreAllocatedCount;
        const char *pszStructureName;
        OG_DESTORY_MEMBER_FUNCTION_T pfDestoryMemberFunction;
    } OG_CR_UNIVERSAL_REGISTRAR_INFORMATION;
#if defined __cplusplus
}
#endif
#endif
