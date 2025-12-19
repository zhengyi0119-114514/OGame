#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if !defined OPEN_GAME_STRUCT_DEFINE_H
#define OPEN_GAME_STRUCT_DEFINE_H 1

#if defined WIN32 || defined WINNT || defined _WIN32
#define OG_EXTERN __declspec(dllimport)
#define OG_CDECL __cdecl
#define OG_STDCALL __stdcall
#define OG_INTERNAL
#define OG_PRIVATE static
#else
#define OG_EXTERN extern
#define OG_CDECL __attribute__((__cdecl__))
#define OG_INTERNAL __attribute__((visibility("hidden")))
#define OG_PRIVATE static
#endif

#if defined __cplusplus
extern "C"
{
#endif
/**
 * @brief OpenStg的错误存储结构
 *
 * @note 高32位标识命名模块空间名称，低32位标识错码
 */
typedef uint64_t OG_ERROR;
typedef uint32_t OG_ERROR_NAMESPACE;
typedef uint32_t OG_ERROR_CODE;
#define OG_MAKE_ERROR(Namespace,Code)                   ((OG_ERROR)(Namespace)<<32|(Code))
#define OG_GET_ERROR_NAMESPACE(error)                   ((OG_ERROR_NAMESPACE)((error) >> 32))
#define OG_GET_ERROR_CODE(error)                        ((OG_ERROR_CODE)((error) & 0xFFFFFFFFULL))

typedef unsigned char OG_BYTE;
typedef signed char OG_SBYTE;
typedef bool OG_BOOL;
#define OG_FALSE                                        ((OG_BOOL)false)
#define OG_TRUE                                         ((OG_BOOL)true)
#if !defined TRUE &&!defined FALSE
#define TRUE                                            OG_TRUE
#define FALSE                                           OG_FALSE
#endif

typedef struct {
    OG_ERROR ecErrno;
    const char* pszErrorMessage;
} OgTHREAD_LOCAL_STORAGE_STRUCT;

#define OG_ERROR_NAMESPACE_CORE                         ((OG_ERROR_NAMESPACE)(0x1))
#define OG_ERROR_NAMESPACE_SDL3                         ((OG_ERROR_NAMESPACE)(0x2))

#define OG_ERROR_MESSAGE_NO_ERROR                       ((OG_ERROR_CODE)(0x00000000)) 

#define OG_ERROR_MESSAGE_CORE_TLS_ALLOR_ERROR           ((OG_ERROR_CODE)(0x00000001)) 
#define OG_ERROR_MESSAGE_MEMORY_ERROR                   ((OG_ERROR_CODE)(0x00000002))
#define OG_ERROR_MESSAGE_INVALID_PARAMETER              ((OG_ERROR_CODE)(0x00000003))
#define OG_ERROR_MESSAGE_MODULE_EXIST                   ((OG_ERROR_CODE)(0x00000004))
#define OG_ERROR_MESSAGE_NOT_INITIALIZED                ((OG_ERROR_CODE)(0x00000005))

#define OG_ERROR_MESSAGE_SDL3_INIT_FAILED               ((OG_ERROR_CODE)(0x00000001))
/**
 * @brief 模块初始化设置
 * 
 * 设置OgINIT_PROGRAM_MODULE_FLAG_ALLOC_STATIC_HANDLE以分配固定句柄
 *
 * @sa ModuleRegisteredFlag
 * @since 0.1.0 
 */
typedef uint64_t ModuleRegisteredFlag;
#define OG_INIT_PROGRAM_MODULE_FLAG_ALLOC_STATIC_HANDLE  \
        ((ModuleRegisteredFlag)UINT64_C(0x0000000000000001))    ///< 当设置此项时 in_out_uModuleHandle 值有效，分配的句柄即 in_out_uModuleHandle 值
typedef void (*OG_CDECL OgGetErrorMessageFunction)
        (OG_ERROR_CODE code, char *pszBuffer,uint64_t uLengthOfBuffer);
#if defined __cplusplus
}
#endif
#endif
