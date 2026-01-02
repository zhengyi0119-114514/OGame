#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if !defined OPEN_GAME_STRUCT_DEFINE_H
#define OPEN_GAME_STRUCT_DEFINE_H 1

#if defined OPEN_STG_MACRO_IS_WINDOWS || defined WINNT || defined _WIN32
    #define OG_EXPORT __declspec(dllexport)
    #define OG_CDECL __cdecl
    #define OG_STDCALL __stdcall
    #define OG_INTERNAL
#elif defined __unix__ || defined __unix
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
typedef uint64_t OG_ERROR_T;
#define OG_ERROR_C(x)                                           UINT64_C(x)
typedef uint32_t OG_MODULE_NAMESPACE_T ;
#define OG_MODULE_NAMESPACE_C(x)                                UINT32_C(x)
typedef uint32_t OG_ERROR_CODE_T;
#define OG_ERROR_CODE_C(x)                                      UINT32_C(x)

#define OgCrMakeError(Namespace,Code)                           ((OG_ERROR_T)(Namespace)<<32|(Code))
#define OgCrGetErrorNamesoace(error)                            ((OG_MODULE_NAMESPACE_T)((error) >> 32))
#define OgCrGetErrorCode(error)                                 ((OG_ERROR_CODE_T)((error) & 0xFFFFFFFFULL))

typedef unsigned char OG_BYTE_T;
typedef signed char OG_SBYTE_T;
typedef bool BOOL_T;
#define OG_FALSE                                        false
#define OG_TRUE                                         true
#if !defined TRUE &&!defined FALSE
#define TRUE                                            OG_TRUE
#define FALSE                                           OG_FALSE
#endif
typedef const char *OG_PCSTR_T;
typedef char *OG_PSTR_T;


#define OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH   ((uint64_t)UINT64_C(128))

#define OPEN_STG_NAMESPACE_CORE                                 ((OG_MODULE_NAMESPACE_T)OG_MODULE_NAMESPACE_C(0x1))
#define OPEN_STG_NAMESPACE_SDL3                                 ((OG_MODULE_NAMESPACE_T)OG_MODULE_NAMESPACE_C(0x2)) 

#define OPEN_STG_ERROR_MESSAGE_NO_ERROR                         ((OG_ERROR_CODE_T)OG_ERROR_CODE_C(0x00000000)) 

#define OPEN_STG_ERROR_MESSAGE_CORE_TLS_ALLOR_ERROR             ((OG_ERROR_CODE_T)OG_ERROR_CODE_C(0x00000001))
#define OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR                     ((OG_ERROR_CODE_T)OG_ERROR_CODE_C(0x00000002))
#define OPEN_STG_ERROR_MESSAGE_UNDEFINED_MEMORY_ERROR           ((OG_ERROR_CODE_T)OG_ERROR_CODE_C(0x00000003))
#define OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER                ((OG_ERROR_CODE_T)OG_ERROR_CODE_C(0x00000004))
#define OPEN_STG_ERROR_MESSAGE_MODULE_EXIST                     ((OG_ERROR_CODE_T)OG_ERROR_CODE_C(0x00000005))
#define OPEN_STG_ERROR_MESSAGE_NOT_INITIALIZED                  ((OG_ERROR_CODE_T)OG_ERROR_CODE_C(0x00000006))

#define OPEN_STG_ERROR_MESSAGE_SDL3_INIT_FAILED                 ((OG_ERROR_CODE_T)OG_ERROR_CODE_C(0x00000001))
typedef struct {
    char pszAdditionalErrorMessage[OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH];
    OG_ERROR_T ecErrno; 
    BOOL_T bIsRecoverableException;
} OG_THREAD_LOCAL_STORAGE_STRUCT;
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
 * 
 */
typedef uint32_t OG_CR_UNIVERSAL_REGISTRAR_FLAG_T;
#define OG_UNIVERSAL_REGISTRAR_FLAG_C(x)                        UINT64_C(x)
#define OPEN_STG_FLAG_UNIVERSAL_REGISTRAR_NONE                          \
        ((OG_CR_UNIVERSAL_REGISTRAR_FLAG_T)OG_UNIVERSAL_REGISTRAR_FLAG_C(0x0000000000000000))
#define OPEN_STG_FLAG_UNIVERSAL_REGISTRAR_NOT_INITIALIZED               \
        ((OG_CR_UNIVERSAL_REGISTRAR_FLAG_T)OG_UNIVERSAL_REGISTRAR_FLAG_C(0x0000000000000001)) 
typedef void (OG_CDECL* OG_DESTORY_MEMBER_FUNCTION_T)(void*);
typedef void (OG_CDECL* OG_FORMAT_ERROR_MESSAGE_FUNCTION_T)(OG_ERROR_CODE_T code, char *pszBuffer,uint64_t uLengthOfBuffer);

#if defined __cplusplus
}
#endif
#endif
