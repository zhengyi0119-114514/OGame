#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if !defined OPEN_GAME_STRUCT_DEFINE_H
#define OPEN_GAME_STRUCT_DEFINE_H 1

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
#if defined __GNUC__
#define OPEN_STG_MACRO_FUNCTION __PRETTY_FUNCTION__
#elif defined _MSC_VER
#define OPEN_STG_MACRO_FUNCTION __FUNCDNAME__
#else
#define OPEN_STG_MACRO_FUNCTION __func__
#endif
/**
 * @brief OpenStg的错误存储结构
 *
 * @note 高32位标识命名模块空间名称，低32位标识错码
 */
typedef uint64_t OG_ERROR;
typedef uint32_t OG_ERROR_NAMESPACE;
typedef uint32_t OG_ERROR_CODE;
#define OgMakeError(Namespace,Code)                     ((OG_ERROR)(Namespace)<<32|(Code))
#define OgGetErrorNamespace(error)                      ((OG_ERROR_NAMESPACE)((error) >> 32))
#define OgGetErrorCode(error)                           ((OG_ERROR_CODE)((error) & 0xFFFFFFFFULL))

typedef unsigned char OG_BYTE;
typedef signed char OG_SBYTE;
typedef bool OG_BOOL;
#define OG_FALSE                                        ((OG_BOOL)false)
#define OG_TRUE                                         ((OG_BOOL)true)
#if !defined TRUE &&!defined FALSE
#define TRUE                                            OG_TRUE
#define FALSE                                           OG_FALSE
#endif


#define OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH   ((uint64_t)UINT64_C(128))

#define OPEN_STG_NAMESPACE_CORE                                 ((OG_ERROR_NAMESPACE)(0x1))
#define OPEN_STG_NAMESPACE_SDL3                                 ((OG_ERROR_NAMESPACE)(0x2))

#define OPEN_STG_ERROR_MESSAGE_NO_ERROR                         ((OG_ERROR_CODE)(0x00000000)) 

#define OPEN_STG_ERROR_MESSAGE_CORE_TLS_ALLOR_ERROR             ((OG_ERROR_CODE)(0x00000001)) 
#define OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR                     ((OG_ERROR_CODE)(0x00000002))
#define OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER                ((OG_ERROR_CODE)(0x00000003))
#define OPEN_STG_ERROR_MESSAGE_MODULE_EXIST                     ((OG_ERROR_CODE)(0x00000004))
#define OPEN_STG_ERROR_MESSAGE_NOT_INITIALIZED                  ((OG_ERROR_CODE)(0x00000005))

#define OPEN_STG_ERROR_MESSAGE_SDL3_INIT_FAILED                 ((OG_ERROR_CODE)(0x00000001))
typedef struct {
    char pszAdditionalErrorMessage[OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH];
    OG_ERROR ecErrno; 
} OG_THREAD_LOCAL_STORAGE_STRUCT;
/**
 * @brief 模块初始化设置
 * 
 * 设置OgINIT_PROGRAM_MODULE_FLAG_ALLOC_STATIC_HANDLE以分配固定句柄
 *
 * @sa ModuleRegisteredFlag
 * @since 0.1.0 
 */
typedef uint64_t ModuleRegisteredFlag;
#define OPEN_STG_FLAG_MODULE_ALLOC_STATIC_HANDLE  \
        ((ModuleRegisteredFlag)UINT64_C(0x0000000000000001))    ///< 当设置此项时 in_out_uModuleHandle 值有效，分配的句柄即 in_out_uModuleHandle 值
typedef void (*OG_CDECL OgGetErrorMessageFunction)
        (OG_ERROR_CODE code, char *pszBuffer,uint64_t uLengthOfBuffer);

#if defined __cplusplus
}
#endif
#endif
