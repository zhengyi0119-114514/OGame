#include <stddef.h>
#include <stdint.h>

#ifndef ogame_api

#if defined __cplusplus
    #define ogmae_c_api_1 extern "C" 
#else
    #define ogmae_c_api_1
    #include <stdbool.h>
#endif

#if defined _WIN32
    #define ogame_api_export __declspec(dllexport)
    #define ogame_api_private
    #define ogame_api_import __declspec(dllimport)
#else
    #define ogame_api_import 
    #define ogame_api_private 
    #define ogame_api_export
#endif

#define null NULL
#define var auto

#ifdef ogame_export
    #define ogame_api ogmae_c_api_1 ogame_api_export
#else
    #define ogame_api ogmae_c_api_1 ogame_api_import
#endif

typedef uint32_t OGAME_RESULT;

//ERROR
#define OGAME_ERROR_NO_ERROR                    ((OGAME_RESULT)0x00000000)
#define OGAME_ERROR_ARGUEMENT_IS_NULL           ((OGAME_RESULT)0x00000001)
#define OGAME_ERROR_INIT_FAILD                  ((OGAME_RESULT)0x00000002)

//OS NAME
#define OGAME_INFO_WINDOWS                      ((uint32_t)1)
#define OGAME_INFO_LINUX                        ((uint32_t)2)
#define OGAME_INFO_MACOS                        ((uint32_t)3)

#endif 