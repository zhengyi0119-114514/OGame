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

#ifndef OPEN_GAME_PRIVATE_H
#define OPEN_GAME_PRIVATE_H 1
#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct OG_ELECTROMAGNETIC_DOT_TIMER_ OG_ELECTROMAGNETIC_DOT_TIMER;
    // 计时器
    OG_EXPORT OG_ELECTROMAGNETIC_DOT_TIMER * OG_CDECL OgCreateElectromagneticDotTimer(int8_t iDotFrequency);
    OG_EXPORT int64_t  OG_CDECL OgElectromagneticDotTimerPullTask(OG_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT void  OG_CDECL OgElectromagneticDotTimerSkipATimeStamp(OG_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT  void OG_CDECL OgRefreshElectromagneticDotTimer(OG_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT  void OG_CDECL OgDestoryElectromagneticDotTimer(OG_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    // 初始化
    OG_EXPORT OG_BOOL_T OG_CDECL OgInit(uint64_t ufInitFlag);
    OG_EXPORT OG_BOOL_T OG_CDECL OgQuit(void);
    // 线程局部存储
    OG_EXPORT  OG_THREAD_LOCAL_STORAGE_STRUCT *OG_CDECL OgGetTLSStruct(void);
#define OG_ERRNO (OgGetTLSStruct()->ecErrno)
#define OG_ERROR_MESSAGE (OgGetTLSStruct()->pszAdditionalErrorMessage)
    OG_INTERNAL OG_BOOL_T OG_CDECL inilTSL(uint64_t ufInitFlag);
    // SDL
    OG_INTERNAL OG_BOOL_T OG_CDECL initSDL(void);
    // 错误处理
    OG_INTERNAL void OG_CDECL setError(OG_ERROR_CODE_T ec);
    OG_INTERNAL void OG_CDECL setErrorAndMessage(const char *pszFile, const char *pszFunction, uint32_t uLine,
                                                 OG_ERROR_T eErrno, const char *pszMessage);
#define SET_ERROR_AND_MESSAGE(errno, message)                                                                          \
    setErrorAndMessage(__FILE__, OPEN_STG_MACRO_FUNCTION, __LINE__, (errno), (message))
    OG_EXPORT void OG_CDECL OgCrGetErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer);
    OG_EXPORT void OG_CDECL OgSdlGetErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer);
    OG_EXPORT void OG_CDECL OgGetErrorMessage(OG_ERROR_T eError, char *pszBuffer, uint64_t uLengthOfBuffer);
    // 模块管理
    typedef struct OgTagPROGRAM_DATA
    {
        OG_PROGRAM_MODULE_PRIVATE *rgModules;
        uint32_t uCountOfReserved;
    } OG_PROGRAM_DATA_T;
    OG_EXPORT OG_BOOL_T OG_CDECL  OgRegisteredProgramModule(const OG_PROGRAM_MODULE_PUBLIC *pModule);
    OG_INTERNAL OG_BOOL_T OG_CDECL  initProgramData(uint32_t uInternalModuleCount);
    OG_INTERNAL OG_BOOL_T OG_CDECL  freeProgramData();
    OG_INTERNAL  OG_PROGRAM_DATA_T *OG_CDECL getProgramData();
    OG_INTERNAL OG_BOOL_T OG_CDECL  reserveModule(uint32_t uCount);
    /**
     * @param sPreAllocIndex 默认为负数
     */
    OG_INTERNAL OG_BOOL_T OG_CDECL  allocModule(OG_PROGRAM_MODULE_PUBLIC **ppModule, int64_t sPreAllocIndex,
                                             uint32_t *piIndex);
    OG_INTERNAL OG_BOOL_T OG_CDECL  initModuleContainer(uint32_t uCount);
    OG_INTERNAL OG_BOOL_T OG_CDECL  freeModuleContainer();

#ifdef __cplusplus
}
#endif
#endif
