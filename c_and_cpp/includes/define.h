#include <stddef.h>
#include <stdint.h>

#ifndef ogame_api

#if defined __cplusplus
    #define ogmae_c_api_1 extern "C" 
#else
    #define ogmae_c_api_1
#endif

#if defined _WIN32
    #define ogame_api_export __declspec(dllexport)
    #define ogame_api_private
    #define ogame_api_import __declspec(dllimport)
#else
    #define ogame_api_import extern
    #define ogame_api_private __attribute__((hidden))
    #define ogame_api_export
#endif

#define null NULL

#ifdef ogame_export
    #define ogame_api ogmae_c_api_1 ogame_api_export
#else
    #define ogame_api ogmae_c_api_1 ogame_api_import
#endif

typedef uint32_t OGAME_RESULT;

#define OGAME_NO_ERROR ((ogame_error_code)0)
#define OGAME_ARGUEMENT_IS_NULL ((ogame_error_code)0x0001)

#endif