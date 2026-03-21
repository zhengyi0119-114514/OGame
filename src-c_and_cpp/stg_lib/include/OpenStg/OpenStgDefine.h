#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
// #include <stdalign.h>

#if !defined OPEN_GAME_STRUCT_DEFINE_H
#define OPEN_GAME_STRUCT_DEFINE_H 1

#if OPEN_STG_MACRO_IS_WINDOWS || defined WINNT || defined _WIN32
    #define OG_EXPORT __declspec(dllexport)
    #if defined __i386__ || defined __x86_64__ || defined _M_IX86 || defined _M_X64
        #define OG_CDECL __cdecl
        #define OG_STDCALL __stdcall
        #define OG_API OG_CDECL
    #else
        #define OG_API
    #endif
    #define OG_INTERNAL
#elif defined __unix__ || defined __unix
    #define OG_EXPORT
    #if defined __x86_64__ || defined __i386__
        #define OG_CDECL __attribute__((__cdecl__))
        #define OG_API OG_CDECL
    #else
        #define OG_API
    #endif
    #define OG_INTERNAL __attribute__((visibility("hidden")))
#endif

#define OG_PRIVATE static
#define OG_EXTERN extern
#if defined _MSC_VER
    #define OG_NORERETURN __declspec(noreturn)
    #define OPEN_STG_MACRO_FUNCTION __FUNCDNAME__
    #define OG_ALWAYS_INLINE
    #define OG_DEPRECATED __declspec(deprecated)
    #define OG_NOINLINE  __declspec(noinline)
#elif defined __GNUC__ 
    #define OG_NORERETURN __attribute__((__noreturn__))
    #define OG_ALWAYS_INLINE __attribute__((__always_inline__))
    #define OG_NOINLINE __attribute__((__noinline__))
    #define OPEN_STG_MACRO_FUNCTION __PRETTY_FUNCTION__
    #define OG_DEPRECATED __attribute__((__deprecated__))
#else
    #define OPEN_STG_MACRO_FUNCTION __func__
    #if __has_include("stdnoreturn.h")
        #include<stdnoreturn.h>
    #endif
    #if defined noreturn
        #define OG_NORERETURN noreturn
    #else
        #define OG_NORERETURN
    #endif
#endif
// aligned
#if defined _MSC_VER
    #define OG_ALIGNED_BEFORE_STRUCT(a) __declspec(align(a))
    #define OG_ALIGNED_AFTER_STRUCT(a)
#elif defined __GNUC__ || defined __llvm__
    #if !defined __llvm__ && !defined __clang__
        #define OG_ALIGNED_BEFORE_STRUCT(a) _Alignas(a)
    #else
        #define OG_ALIGNED_BEFORE_STRUCT(a)
    #endif
    #define OG_ALIGNED_AFTER_STRUCT(a) __attribute__((__aligned__(a)))
#endif

#if defined __GNUC__
    #define OG_CONST __attribute__((__const__))
    #define OG_GUN_ATTRIBUTE(e) e
#endif

#if defined __cplusplus
extern "C"
{
#endif
typedef unsigned char BYTE_T;
typedef signed char SBYTE_T;
typedef bool BOOL_T;
#define OG_FALSE                                                false
#define OG_TRUE                                                 true
#if !defined TRUE &&!defined FALSE
    #define TRUE                                                OG_TRUE
    #define FALSE                                               OG_FALSE
#endif

#define OgCrMakeError(Namespace,Code)                           ((OG_ERROR_T)(Namespace)<<32|(Code))
#define OgCrGetErrorNamespace(error)                            ((OG_MODULE_NAMESPACE_T)((error) >> 32))
#define OgCrGetErrorCode(error)                                 ((OG_ERROR_CODE_T)((error) & 0xFFFFFFFFULL))

#define OPEN_STG_NAMESPACE_CORE                                 ((OG_MODULE_NAMESPACE_T)OG_MODULE_NAMESPACE_C(0x1))
#define OPEN_STG_NAMESPACE_GRAPHICS                             ((OG_MODULE_NAMESPACE_T)OG_MODULE_NAMESPACE_C(0x2))
#define OPEN_STG_NAMESPACE_NETWORK                              ((OG_MODULE_NAMESPACE_T)OG_MODULE_NAMESPACE_C(0x3))
#define OPEN_STG_NAMESPACE_LOGIC                                ((OG_MODULE_NAMESPACE_T)OG_MODULE_NAMESPACE_C(0x4))

#define OPEN_STG_ERROR_CODE_CORE_UNKNOWN_EXCEPTION              (OG_ERROR_CODE_C(0x00000000))
#define OPEN_STG_ERROR_CODE_CORE_STL_ALLOC_ERROR                (OG_ERROR_CODE_C(0x00000001))
#define OPEN_STG_ERROR_CODE_CORE_MEMORY_ERROR                   (OG_ERROR_CODE_C(0x00000002))
#define OPEN_STG_ERROR_CODE_CORE_UNDEFINED_MEMORY_ERROR         (OG_ERROR_CODE_C(0x00000003))
#define OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER              (OG_ERROR_CODE_C(0x00000004))
#define OPEN_STG_ERROR_CODE_CORE_MODULE_EXIST                   (OG_ERROR_CODE_C(0x00000005))
#define OPEN_STG_ERROR_CODE_CORE_MODULE_NOT_EXIST               (OG_ERROR_CODE_C(0x00000006))
#define OPEN_STG_ERROR_CODE_CORE_NOT_INITIALIZED                (OG_ERROR_CODE_C(0x00000007))
#define OPEN_STG_ERROR_CODE_CORE_OUT_OF_RANGE                   (OG_ERROR_CODE_C(0x00000008))

#define OPEN_STG_ERROR_CDOE_GRAPHICS_NO_ERROR                   (OG_ERROR_CODE_C(0x00000000))
#define OPEN_STG_ERROR_CODE_GRAPHICS_INIT_FAILED                (OG_ERROR_CODE_C(0x00000001))

#define OPEN_STG_ERRPR_MESSAGE_NETWORK_INIT_FAILED              (OG_ERROR_CODE_C(0x00000001))


/**
 * @brief OpenStg的错误存储结构
 *
 * @note 高32位标识命名模块空间名称，低32位标识错码
 */
typedef uint64_t OG_ERROR_T;
#define OG_ERROR_C(x)                                           UINT64_C(x)
typedef uint32_t OG_MODULE_NAMESPACE_T ;
#define OG_MODULE_NAMESPACE_C(x)                                UINT32_C(x)
typedef uint32_t OG_ERROR_CODE_T;
#define OG_ERROR_CODE_C(x)                                      UINT32_C(x)

#define OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH   (UINT64_C(128))
#define OPEN_STG_CONST_CHAR_BUFFER_LENGTH                       (UINT64_C(256))
#define OPEN_STG_CONST_MAX_EXCEPTION_HANDLER_FUNCTION           (UINT64_C(16))
#define OPEN_STG_CONST_MAX_MODULE_TREE_DEPTH                    (UINT16_C(128))
#define OPEN_STG_CONST_MAX_MODULE_SINGLE_LAYER                  (UINT16_C(128))
#define OPEN_STG_CONST_MAX_MODULE_NUMBER                        \
    ((uint32_t)(OPEN_STG_CONST_MAX_MODULE_TREE_DEPTH)*(uint32_t)(OPEN_STG_CONST_MAX_MODULE_SINGLE_LAYER))
#define OPEN_STG_CONST_NUMBER_OF_RESERVERD_MODULES              (UINT32_C(10))
#define OPEN_STG_CONST_MAX_NAME_LENGTH                          (UINT16_C(128))

typedef struct TagOgCrTHREAD_LOCAL_STORAGE_STRUCT{
    char szUniversalBuffer[OPEN_STG_CONST_CHAR_BUFFER_LENGTH];
    char szAdditionalErrorMessage[OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH];
    OG_ERROR_T ecErrno;
    BOOL_T bIsRecoverableException;
} OG_CR_THREAD_LOCAL_STORAGE_STRUCT;

typedef void (OG_API* OG_CR_DESTORY_MEMBER_FUNCTION_T)(void*);

/**
 * @brief 物理课的杀人魔
 *
 * 一个神奇的计时器，内部维护着一个任务列表，每秒往列表中塞iFrequency个任务
 * 用于控制1秒内的计算次数，拥有较高的精度
 * 该Timer的实现与平台类型高度相关，故隐藏实现
 * 调用OgCrCreateElectromagneticDotTimer()创建计时器
 * 调用OgCrElectromagneticDotTimerPullTask()把陈年老账拉起来鞭尸(计算队列中的任务数)，
 * 调用OgCrElectromagneticDotTimerSkipATimeStamp()则等待到下一个加入队列，并清空队列
 * 调用OgCrRefreshElectromagneticDotTimer()重置计时器
 * 调用OgCrDestoryElectromagneticDotTimer()销毁计时器
 *
 * @note 本计时器设计时仅考虑了单线程场景
 * @since 0.1.0
 * @anchor IceThorn
 * @date 2025/11/23
 * @sa
 * @sa OgCrDestoryElectromagneticDotTimer
 * @sa OgCrElectromagneticDotTimerPullTask
 * @sa OgCrElectromagneticDotTimerSkipATimeStamp
 * @sa OgCrRefreshElectromagneticDotTimer
 */
typedef struct TagOgCrELECTROMAGNETIC_DOT_TIMER OG_CR_ELECTROMAGNETIC_DOT_TIMER;

/**
 * @brief 通用注册项容器(通用注册器)
 *
 * @note 内部的主要结构是一个目标类型数组和一个布尔数组
 */
typedef struct TagOgCrUNIVERSAL_REGISTRAR OG_CR_UNIVERSAL_REGISTRAR;

/**
 * @brief 通用注册器迭代器
 *
 * @note 内部维护一个索引
 */
typedef struct TagOgCrUNIVERSAL_REGISTRAR_ITERATOR OG_CR_UNIVERSAL_REGISTRAR_ITERATOR;

typedef void (OG_API* OG_CR_FORMAT_ERROR_MESSAGE_FUNCTION_T)(
    OG_ERROR_CODE_T code,
    char *pszBuffer,
    uint64_t uLengthOfBuffer
);

/**
 * @brief 这个函数将会在依赖树构建完成后按依赖顺序调用
 */
typedef void (OG_API* OG_CR_INITALZATION_FUNCTION_T)(void *pvAdditionalData);

typedef void (OG_API* OG_CR_DESTORY_PROGRAM_MODULE_T)();

typedef void (OG_API* OG_CR_MODULE_ADDITIONAL_RELEASE_FUNCTION_T)(void*);

/**
 * @brief 模块初始化设置
 *
 * 设置OgINIT_PROGRAM_MODULE_FLAG_ALLOC_STATIC_HANDLE以分配固定句柄
 * OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE位志使OgCrRegisterProgramModule函数分配固定的空间名称
 * @since 0.1.0
 */
typedef uint64_t OG_MODULE_REGISTERED_FLAG_T;
#define OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE                        \
        ((OG_MODULE_REGISTERED_FLAG_T)UINT64_C(0x0000000000000001))

/**
 * @brief 通用注册器初始化设置
 */
typedef uint64_t OG_CR_UNIVERSAL_REGISTRAR_FLAG_T;
#define OG_UNIVERSAL_REGISTRAR_FLAG_C(x)                        UINT64_C(x)
#define OPEN_STG_FLAG_UNIVERSAL_REGISTRAR_NONE                          \
        ((OG_CR_UNIVERSAL_REGISTRAR_FLAG_T)OG_UNIVERSAL_REGISTRAR_FLAG_C(0x0000000000000000))
#define OPEN_STG_FLAG_UNIVERSAL_REGISTRAR_NOT_INITIALIZED               \
        ((OG_CR_UNIVERSAL_REGISTRAR_FLAG_T)OG_UNIVERSAL_REGISTRAR_FLAG_C(0x0000000000000001))

#define OPEN_STG_REGISTRAR_NAME_CORE                                    "ice_thorn.core.cirno_baka"
#define OPEN_STG_REGISTRAR_NAME_GRAPHICS                                "ice_thorn.graphics.just_arch_linux"
#define OPEN_STG_REGISTRAR_NAME_NETWORK                                 "ice_thorn.network.emotional_damage"
/**
 * @brief 注册模块时的参数
 *
 * //NOTE: 改动时手动更改OgCrRegisterProgramModule()函数
 *
 * @note fnFreeFunc先于fnDestoryProgramModule调用
 */
typedef struct TagOgCrPROGRAM_MODULE
{
    int64_t iSize;                                              ///< (REQUIRED)版本控制，总应该初始化为sizeof(OG_CR_PROGRAM_MODULE)
    OG_MODULE_REGISTERED_FLAG_T ufModuleRegisteredFlag;         ///< 输入，位志符
    const char *pszModuleDisplayName;                           ///< 输入，模块显示名称，如果为NULL，则会被设置为
                                                                ///< pszRegisteredName
    union {
        const char *pszModuleRegisteredName;                    ///< (REQUIRED)输入，注册名称，必须是唯一的，
                                                                ///< 等同与 pszRegisteredId
        const char *pszModuleRegisteredId;                      ///< 注册ID，必须是唯一的，等同与 pszRegisteredName
        intptr_t iPlaceholder;                                  ///< 这个字段为什么会有用？😄️
    };
    OG_CR_FORMAT_ERROR_MESSAGE_FUNCTION_T fnFormatErrorMessage; ///< (REQUIRED)输入，获取错误码对应的字符串描述函数
    OG_CR_DESTORY_PROGRAM_MODULE_T fnDestoryProgramModule;      ///< 输入，模块的销毁函数
    OG_CR_INITALZATION_FUNCTION_T fnPostInitalzationFunction;   ///< 输入，这个函数将会在依赖树构建完成后按依赖顺序调用
    void *pvAdditionalData;                                     ///< 输入，模块额外信息
    OG_CR_MODULE_ADDITIONAL_RELEASE_FUNCTION_T fnFreeFunc;      ///< (REQUIRED)输入，模块额外信息释放函数
    const char **rgpszDependenciesRegisteredName;               ///< 输入，指向一个字符串数组，包涵依赖项的注册名
    uint32_t uCountOfDependencies;                              ///< 输入，指示rgpszDependenciesRegisteredName成员的个数
    OG_MODULE_NAMESPACE_T uModuleNamespace;                     ///< 输出，设置为模块空间名称
} OG_CR_PROGRAM_MODULE;

/**
 * @brief 模块迭代器，检索已注册的模块
 * @note 模块成员不公开，线程不安全
 */
typedef struct TagOgCrPROGRAM_MODULE_ITREATOR OG_CR_PROGRAM_MODULE_ITERATOR;

/**
 * @brief 通用注册器创建信息
 */
typedef struct TagOgCrUNIVERSAL_REGISTRAR_INFORMATION
{
    uint64_t uSize;                                 ///< (REQUIRED)版本控制，总应该初始化为
                                                    ///< sizeof(OG_CR_UNIVERSAL_REGISTRAR_INFORMATION)
    OG_CR_UNIVERSAL_REGISTRAR_FLAG_T ufCreateFlags; ///< 输入，位志符
    const char* pszStructureName;
    uint64_t uUnitStructureSize;                    ///< 输入，单位结构大小
    uint64_t uPreAllocatedCount;                    ///< 输入，预分配结构大小
    OG_CR_DESTORY_MEMBER_FUNCTION_T pfDestoryMember;
}OG_CR_UNIVERSAL_REGISTRAR_INFORMATION;

#define OPEN_STG_CONST_MAX_UNIT_STRUCTURE_SIZE  UINT64_C(256*1024*1024)
#define OPEN_STG_CONST_MAX_STRUCTURE_COUNT      UINT64_C(68719476736)

/**
 * @brief 程序模块句柄
 */
typedef int64_t PROGRAM_MODULE_HANDLE;

OG_ALIGNED_BEFORE_STRUCT(8)
struct OG_ALIGNED_AFTER_STRUCT(8) TagOgCrEXCEPTION_HANDLER_STATUS
{
    BOOL_T bContinue;
    uint8_t uOperatorFlag;
    uint16_t uPlaceholder0;
    uint32_t uPlaceholder1;
};
typedef struct TagOgCrEXCEPTION_HANDLER_STATUS OG_CR_EXCEPTION_HANDLER_STATUS;
typedef OG_CR_EXCEPTION_HANDLER_STATUS (OG_API* OG_CR_EXCEPTION_HANDLER_FUNCTION_T)(OG_ERROR_T e,BOOL_T bIsRecoverableException);
#if defined __cplusplus
}
#endif
#endif
