#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

#if __has_include("safec.h")
#include <safec.h>
#endif
#include "CloseStgHistory.h"
#include <OpenStgDefine.h>

#if defined WIN32 || defined WINNT
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

#ifndef OPEN_GAME_PRIVATE_H
#define OPEN_GAME_PRIVATE_H 1
#ifdef __cplusplus
extern "C"
{
#endif
#ifdef _WIN32
    typedef struct OgELECTROMAGNETIC_DOT_TIMER_
    {
        LARGE_INTEGER *pliDotTable;
        LARGE_INTEGER liFrequency;
        LARGE_INTEGER liStart;
        LARGE_INTEGER liLast;
        int8_t iFrequency;
    } OgELECTROMAGNETIC_DOT_TIMER;
#elif defined __unix__ || defined __unix
typedef struct OgELECTROMAGNETIC_DOT_TIMER_
{
    int64_t *piDotTable;
    struct timespec tsLast;
    struct timespec tsStart;
    int8_t iFrequency;
} OgELECTROMAGNETIC_DOT_TIMER;
#endif
    // 计时器
    OG_EXPORT OG_CDECL OgELECTROMAGNETIC_DOT_TIMER *OgCreateElectromagneticDotTimer(int8_t iFrequency);
    OG_EXPORT OG_CDECL int64_t OgElectromagneticDotTimerPullTask(OgELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT OG_CDECL void OgElectromagneticDotTimerSkipATimeStamp(OgELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT OG_CDECL void OgRefreshElectromagneticDotTimer(OgELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT OG_CDECL void OgDestoryElectromagneticDotTimer(OgELECTROMAGNETIC_DOT_TIMER *pEdt);
    // 初始化
    OG_EXPORT OG_CDECL OG_BOOL OgInit(uint64_t ufInitFlag);
    OG_EXPORT OG_CDECL OG_BOOL OgQuit(void);
    // 线程局部存储
    OG_EXPORT OG_CDECL OgTHREAD_LOCAL_STORAGE_STRUCT *OgGetTLSStruct(void);
#define OG_ERRNO (OgGetTLSStruct()->ecErrno)
#define OG_ERROR_MESSAGE (OgGetTLSStruct()->pszErrorMessage)
    OG_INTERNAL OG_CDECL OG_BOOL inilTSL(uint64_t ufInitFlag);
    // SDL
    OG_INTERNAL OG_CDECL OG_BOOL initSDL(void);
    // 错误处理
    OG_INTERNAL OG_CDECL void setError(OG_ERROR_CODE ec);
    OG_EXPORT OG_CDECL void OgCoreGetErrorMessage(OG_ERROR_CODE code, char *pszBuffer, uint64_t uLengthOfBuffer);
    OG_EXPORT OG_CDECL void OgSdlGetErrorMessage(OG_ERROR_CODE code, char *pszBuffer, uint64_t uLengthOfBuffer);
    OG_EXPORT OG_CDECL void OgGetErrorMessage(OG_ERROR eError, char *pszBuffer, uint64_t uLengthOfBuffer);
    // 模块管理
    typedef struct OgTagPROGRAM_DATA
    {
        OG_RPOGRAM_MODULE_PRIVATE *rgModules;
        uint32_t uCountOfReserved;
    } OG_PROGRAM_DATA;
    OG_EXPORT OG_CDECL OG_BOOL OgRegisteredProgramModule(const OG_PROGRAM_MODULE_PUBLIC *pModule);
    OG_INTERNAL OG_CDECL OG_BOOL initProgramData(uint32_t uInternalModuleCount);
    OG_INTERNAL OG_CDECL OG_BOOL freeProgramData();
    OG_INTERNAL OG_CDECL OG_PROGRAM_DATA *getProgramData();
    OG_INTERNAL OG_CDECL OG_BOOL reserveModule(uint32_t uCount);
    /**
     * @param sPreAllocIndex 默认为负数 
     */
    OG_INTERNAL OG_CDECL OG_BOOL allocModule(OG_PROGRAM_MODULE_PUBLIC **ppModule,int64_t sPreAllocIndex,uint32_t* piIndex);
    OG_INTERNAL OG_CDECL OG_BOOL initModuleContainer(uint32_t uCount);
    OG_INTERNAL OG_CDECL OG_BOOL freeModuleContainer();

#ifdef __cplusplus
}
#endif
#endif
