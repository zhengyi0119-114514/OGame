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
    typedef struct TagOG_ELECTROMAGNETIC_DOT_TIMER OG_ELECTROMAGNETIC_DOT_TIMER;
    // 计时器
    OG_EXPORT OG_ELECTROMAGNETIC_DOT_TIMER *OG_CDECL OgCrCreateElectromagneticDotTimer(int8_t iDotFrequency);
    OG_EXPORT int64_t OG_CDECL OgCrElectromagneticDotTimerPullTask(OG_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT void OG_CDECL OgCrElectromagneticDotTimerSkipATimeStamp(OG_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT void OG_CDECL OgCrRefreshElectromagneticDotTimer(OG_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT void OG_CDECL OgCrDestoryElectromagneticDotTimer(OG_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    // 初始化
    OG_EXPORT BOOL_T OG_CDECL OgInit(uint64_t ufInitFlag);
    OG_EXPORT BOOL_T OG_CDECL OgQuit(void);
    OG_EXPORT void OG_CDECL OgFormatErrorMessage(OG_ERROR_T eError, char *pszBuffer, uint64_t uLengthOfBuffer);

    /*******
     * Core *
     *******/
    OG_EXPORT BOOL_T OG_CDECL OgCrInit();
    // 线程局部存储
    OG_EXPORT OG_THREAD_LOCAL_STORAGE_STRUCT *OG_CDECL OgCrGetTLSStruct(void);
#define OG_ERRNO (OgCrGetTLSStruct()->ecErrno)
#define OG_ERROR_MESSAGE (OgCrGetTLSStruct()->pszAdditionalErrorMessage)
#define OG_ERROR_RECOVERABLE (OgCrGetTLSStruct()->bIsRecoverableException) ///< 线程独立的ErrorReconverable字段

    OG_INTERNAL BOOL_T OG_CDECL crInitTSL(uint64_t ufInitFlag);
    OG_INTERNAL BOOL_T OG_CDECL crFreeTSL(void);
    // 错误处理
    OG_INTERNAL void OG_CDECL setCrRecoverableError(OG_ERROR_CODE_T ec);
    OG_INTERNAL void OG_CDECL setCrIrreversibleError(OG_ERROR_CODE_T ec);
    OG_INTERNAL void OG_CDECL setErrorAndMessage(const char *pszFile, const char *pszFunction, uint32_t uLine,
                                                 OG_ERROR_T eErrno, const char *pszMessage);
#define SET_ERROR_AND_MESSAGE(errno, message)                                                                          \
    setErrorAndMessage(__FILE__, OPEN_STG_MACRO_FUNCTION, __LINE__, (errno), (message))
    OG_EXPORT void OG_CDECL OgCrFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer);
    OG_EXPORT void OG_CDECL OgSdlFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer);
    // 模块管理
    OG_EXPORT BOOL_T OG_CDECL OgCrRegisterProgramModule(const OG_CR_PROGRAM_MODULE *mod, uint32_t *puNamespaceOutput);
    OG_EXPORT BOOL_T OG_CDECL OgCrUnregisterProgramModule(const char *pszModuleRegisteredName); // TODO: finish it
    typedef struct TagOgCrMODULE_ITREATOR OG_CR_MODULE_ITERATOR;
    OG_EXPORT OG_CR_MODULE_ITERATOR *OG_CDECL OgCrCreateModuleRegistrarIterator();
    OG_EXPORT BOOL_T OG_CDECL OgCrModuleRegistrarIteratorNext(OG_CR_MODULE_ITERATOR *piter, OG_CR_PROGRAM_MODULE *pmod);
    OG_EXPORT void OG_CDECL OgCrDestoryModuleRegistrarIterator(OG_CR_MODULE_ITERATOR *piter);
    // 通用注册器
    OG_INTERNAL BOOL_T OG_CDECL crInitModuleRegistrar(void);
    OG_INTERNAL BOOL_T OG_CDECL crDestroyModuleRegistrar(void);
    typedef struct TagOgCrUNIVERSAL_REGISTRAR OG_CR_UNIVERSAL_REGISTRAR;
    OG_EXPORT OG_CR_UNIVERSAL_REGISTRAR *OG_CDECL
    OgCrCreateUniversalRegistrar(const OG_CR_UNIVERSAL_REGISTRAR_INFORMATION *puri);
    OG_EXPORT BOOL_T OG_CDECL OgCrUniversalRegistrarReserveItems(OG_CR_UNIVERSAL_REGISTRAR *pur,
                                                                 uint32_t uReserveCount);
    OG_EXPORT int64_t OG_CDECL OgCrUniversalRegistrarAllocateItem(OG_CR_UNIVERSAL_REGISTRAR *pur, void **pOutput);
    OG_EXPORT int64_t OG_CDECL OgCrUniversalRegistrarAllocatePreallocatedItem(OG_CR_UNIVERSAL_REGISTRAR *pur,
                                                                              uint32_t uPreAllocatedIndex,
                                                                              void **pOutput);
    OG_EXPORT void *OG_CDECL OgCrUniversalRegistrarGetItem(OG_CR_UNIVERSAL_REGISTRAR *pur, uint32_t uIndex);
    OG_EXPORT BOOL_T OG_CDECL OgCrUniversalRegistrarFreeItem(OG_CR_UNIVERSAL_REGISTRAR *pur, uint32_t uIndex);
    OG_EXPORT void OG_CDECL OgCrDestoryUniversalRegistrar(OG_CR_UNIVERSAL_REGISTRAR *pur);
    typedef struct TagOgCrUNIVERSAL_REGISTRAR_ITERATOR OG_CR_UNIVERSAL_REGISTRAR_ITERATOR;
    OG_EXPORT OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *OgCrCreateUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR *pur);
    OG_EXPORT void *OgCrUniversalRegistrarIteratorNext(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri);
    OG_EXPORT void OgCrDestoryUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri);

    /*******
     * SDL *
     ******/

#ifdef __cplusplus
}
#endif
#endif
