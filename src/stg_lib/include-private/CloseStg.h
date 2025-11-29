#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>
#if __has_include("windows.h")
#include <windows.h>
#endif
#if __has_include("safec.h")
#include <safec.h>
#endif
#include "CloseStgHistory.h"

#if defined WIN32 || defined WINNT
#define OPEN_STG_EXPORT __declspec(dllexport)
#define OPEN_STG_CDECL __cdecl
#define OPEN_STG_STDCALL __stdcall
#define OPEN_STG_INTERNAL 
#else
#define OPEN_STG_EXPORT
#define OPEN_STG_CDECL __attribute__((__cdecl__))
#define OPEN_STG_STDCALL __attribute__((__stdcall__))
#define OPEN_STG_INTERNAL __attribute__((visibility("hidden")))
#endif
#define OPEN_STG_PRIVATE static
#define OPEN_STG_EXTERN extern


#ifndef OPEN_GAME_PRIVATE_H
#define OPEN_GAME_PRIVATE_H 1
#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct OgELECTROMAGNETIC_DOT_TIMER_
    {
#ifdef WIN32
        LARGE_INTEGER *pliDotTable;
        LARGE_INTEGER liFrequency;
        LARGE_INTEGER liStart;
        LARGE_INTEGER liLast;
#elif defined POSIX
        int64_t* piDotTable;
        struct timespec tsLast;
        struct timespec tsStart;
#else
        static_assert(false,"platform not support");
#endif
        int8_t iFrequency;
    } OgELECTROMAGNETIC_DOT_TIMER;
    OPEN_STG_EXPORT OPEN_STG_CDECL OgELECTROMAGNETIC_DOT_TIMER *OgElectromagneticDotTimerCreate(int8_t iFrequency);
    OPEN_STG_EXPORT OPEN_STG_CDECL int64_t OgElectromagneticDotTimerPullTask(OgELECTROMAGNETIC_DOT_TIMER *pEdt);
    OPEN_STG_EXPORT OPEN_STG_CDECL void OgElectromagneticDotTimerSkipATimeStamp(OgELECTROMAGNETIC_DOT_TIMER *pEdt);
    OPEN_STG_EXPORT OPEN_STG_CDECL void OgElectromagneticDotTimerRefresh(OgELECTROMAGNETIC_DOT_TIMER *pEdt);
    OPEN_STG_EXPORT OPEN_STG_CDECL void OgElectromagneticDotTimerDestory(OgELECTROMAGNETIC_DOT_TIMER *pEdt);
#ifdef __cplusplus
}
#endif
#endif
