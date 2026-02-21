/**
 * @file CloseStgCore.h
 * @brief OpenStg 核心模块私有头文件
 *
 * 包含核心模块的内部函数声明和私有定义。
 * 此文件仅供 OpenStg 内部实现使用，不对外公开。
 */

#ifndef OPEN_GAME_PRIVATE_H
#define OPEN_GAME_PRIVATE_H 1

/* 系统头文件 */
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

/* 可选的安全C库 */
#if __has_include("safec.h")
#include <safec.h>
#endif

/* 项目头文件 */
#include "OpenStg/CloseStgHistory.h"
#include <OpenStg/OpenStgDefine.h>

#ifdef __cplusplus
extern "C"
{
#endif
    OG_EXPORT OG_CR_ELECTROMAGNETIC_DOT_TIMER *OG_API OgCrCreateElectromagneticDotTimer(int8_t iDotFrequency);
    OG_EXPORT void OG_API OgCrDestoryElectromagneticDotTimer(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT int64_t OG_API OgCrElectromagneticDotTimerPullTask(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT void OG_API OgCrElectromagneticDotTimerSkipATimeStamp(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT void OG_API OgCrRefreshElectromagneticDotTimer(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt);
    OG_EXPORT void OG_API OgFormatErrorMessage(OG_ERROR_T eError, char *pszBuffer, uint64_t uLengthOfBuffer);
    OG_EXPORT BOOL_T OG_API OgCrRegisterProgramModule(const OG_CR_PROGRAM_MODULE *mod, uint32_t *puNamespaceOutput);
    OG_EXPORT BOOL_T OG_API OgCrUnregisterProgramModule(const char *pszModuleRegisteredName);
    OG_EXPORT OG_CR_PROGRAM_MODULE_ITERATOR *OG_API OgCrCreateProgramModuleRegistrarIterator();
    OG_EXPORT BOOL_T OG_API OgCrProgramModuleRegistrarIteratorNext(OG_CR_PROGRAM_MODULE_ITERATOR *piter,
                                                                   OG_CR_PROGRAM_MODULE *pmod);
    OG_EXPORT int64_t OG_API OgCrUniversalRegistrarGetReservedItemCount(OG_CR_UNIVERSAL_REGISTRAR *pur);
    OG_EXPORT int64_t OG_API OgCrUniversalRegistrarGetAllocatedItemCount(OG_CR_UNIVERSAL_REGISTRAR *pur);
    OG_EXPORT void OG_API OgCrDestoryProgramModuleRegistrarIterator(OG_CR_PROGRAM_MODULE_ITERATOR *piter);
    OG_EXPORT OG_CR_UNIVERSAL_REGISTRAR *OG_API
    OgCrCreateUniversalRegistrar(const OG_CR_UNIVERSAL_REGISTRAR_INFORMATION *puri);
    OG_EXPORT BOOL_T OG_API OgCrUniversalRegistrarReserveItems(OG_CR_UNIVERSAL_REGISTRAR *pur, uint32_t uReserveCount);
    OG_EXPORT int64_t OG_API OgCrUniversalRegistrarAllocateItem(OG_CR_UNIVERSAL_REGISTRAR *pur, void **pOutput);
    OG_EXPORT int64_t OG_API OgCrUniversalRegistrarAllocatePreallocatedItem(OG_CR_UNIVERSAL_REGISTRAR *pur,
                                                                            uint32_t uPreAllocatedIndex,
                                                                            void **pOutput);
    OG_EXPORT void *OG_API OgCrUniversalRegistrarGetItem(OG_CR_UNIVERSAL_REGISTRAR *pur, uint64_t uIndex);
    OG_EXPORT BOOL_T OG_API OgCrUniversalRegistrarFreeItem(OG_CR_UNIVERSAL_REGISTRAR *pur, uint64_t uIndex);
    OG_EXPORT void OG_API OgCrDestoryUniversalRegistrar(OG_CR_UNIVERSAL_REGISTRAR *pur);
    OG_EXPORT OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *OgCrCreateUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR *pur);
    OG_EXPORT void *OG_API OgCrUniversalRegistrarIteratorNext(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri);
    OG_EXPORT void OG_API OgCrDestoryUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri);
    OG_EXPORT PTR_PROGRAM_MODULE OG_API OgCrGetProgramModulePointerByRegistrerdName(const char *pszRegisteredName);
    OG_EXPORT void *OG_API OgCrGetProgramModuleAdditionalData(PTR_PROGRAM_MODULE pModule);
    OG_EXPORT OG_ALWAYS_INLINE void OG_API OgCrPrintStackTrace(void);
    OG_EXPORT void *OG_API OgCrNoExceptPtrVa(void *p);
    OG_EXPORT void *OG_API OgCrNoExceptPtrEx(void *p, const char *pszExpression, const char *pszFunction,
                                             const char *pszFile, uint64_t uLine);
    OG_EXPORT BOOL_T OG_API OgCrNoExceptBooleanVa(BOOL_T b);
    OG_EXPORT BOOL_T OG_API OgCrNoExceptBooleanEx(BOOL_T b, const char *pszExpression, const char *pszFunction,
                                                  const char *pszFile, uint64_t uLine);
#if OPEN_STG_MACRO_IS_DEBUG
#define OgCrNoExceptPtr(p) OgCrNoExceptPtrEx((p), #p, OPEN_STG_MACRO_FUNCTION, __FILE__, __LINE__ + 1)
#define OgCrNoExceptBoolean(b) OgCrNoExceptBooleanEx((b), #b, OPEN_STG_MACRO_FUNCTION, __FILE__, __LINE__ + 1)
#else
#define OgCrNoExceptPtr(p) OgCrNoExceptPtrVa
#define OgCrNoExceptBoolean(b) OgCrNoExceptBooleanVa
#endif
    OG_EXPORT OG_CR_THREAD_LOCAL_STORAGE_STRUCT *OG_API OgCrGetTLSStruct(void);
#define OG_ERRNO (OgCrGetTLSStruct()->ecErrno)
#define OG_ERROR_MESSAGE (OgCrGetTLSStruct()->szAdditionalErrorMessage)
#define OG_ERROR_RECOVERABLE (OgCrGetTLSStruct()->bIsRecoverableException)
    OG_INTERNAL BOOL_T OG_API ogCrPvInitTSL();
    OG_INTERNAL BOOL_T OG_API ogCrPvFreeTSL(void);
    OG_EXPORT void OG_API OgCrSetRecoverableError(OG_ERROR_T ec);
    OG_EXPORT OG_NORERETURN void OG_API OgCrSetIrreversibleError(OG_ERROR_T ec);
    OG_EXPORT void OG_API OgCrFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer);
    OG_EXPORT char *OG_API OgCrGetCharBuffer(void);
    OG_EXPORT void OG_API OgCrSetErrorHandler(OG_CR_EXCEPTION_HANDLER_FUNCTION_T pfnHandler);
#define OG_CHAR_BUFFER OgCrGetCharBuffer()
    OG_INTERNAL BOOL_T OG_API ogCrPvInitModuleRegistrar(void);
    OG_INTERNAL BOOL_T OG_API crDestroyModuleRegistrar(void);
    OG_EXPORT PTR_PROGRAM_MODULE OG_API OgCrGetProgramModulePointerByNamespace(OG_MODULE_NAMESPACE_T uNamespace);
    OG_INTERNAL OG_CR_UNIVERSAL_REGISTRAR *OG_API ogCrCreateProgramStaticVariableContainer();
    OG_EXPORT BOOL_T OG_API OgCrInit();
    inline void *OG_API OG_ALWAYS_INLINE OgCrSetErrorIfValueIsNULL(void *pvValue, OG_ERROR_T uError)
    {
        if (!pvValue)
        {
            OgCrSetRecoverableError(uError);
        }
        return pvValue;
    }
    inline BOOL_T OG_API OG_ALWAYS_INLINE OgCrSetErrorIfValueIsFalse(BOOL_T bValue, OG_ERROR_T uError)
    {
        if (!bValue)
        {
            OgCrSetRecoverableError(uError);
        }
        return bValue;
    }
    OG_INTERNAL BOOL_T OG_API ogCrPvInitProgramStaticVariables(void);
    OG_INTERNAL OG_CR_PV_PROGRAM_STATIC_VARIABLES *OG_API ogCrPvGetProgramStaticVariables(void);
    OG_INTERNAL void OG_API ogCrPvFreeProgramStaticVariables(void);
#ifdef __cplusplus
}
#endif

#endif /* OPEN_GAME_PRIVATE_H */
