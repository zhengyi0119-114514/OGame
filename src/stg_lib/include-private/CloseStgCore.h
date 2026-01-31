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
#include "CloseStgHistory.h"
#include <OpenStgDefine.h>

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
    OG_EXPORT void OG_API OgCrDestoryProgramModuleRegistrarIterator(OG_CR_PROGRAM_MODULE_ITERATOR *piter);
    OG_EXPORT OG_CR_UNIVERSAL_REGISTRAR *OG_API
    OgCrCreateUniversalRegistrar(const OG_CR_UNIVERSAL_REGISTRAR_INFORMATION *puri);
    OG_EXPORT BOOL_T OG_API OgCrUniversalRegistrarReserveItems(OG_CR_UNIVERSAL_REGISTRAR *pur, uint32_t uReserveCount);
    OG_EXPORT int64_t OG_API OgCrUniversalRegistrarAllocateItem(OG_CR_UNIVERSAL_REGISTRAR *pur, void **pOutput);
    OG_EXPORT int64_t OG_API OgCrUniversalRegistrarAllocatePreallocatedItem(OG_CR_UNIVERSAL_REGISTRAR *pur,
                                                                            uint32_t uPreAllocatedIndex,
                                                                            void **pOutput);
    OG_EXPORT void *OG_API OgCrUniversalRegistrarGetItem(OG_CR_UNIVERSAL_REGISTRAR *pur, uint32_t uIndex);
    OG_EXPORT BOOL_T OG_API OgCrUniversalRegistrarFreeItem(OG_CR_UNIVERSAL_REGISTRAR *pur, uint32_t uIndex);
    OG_EXPORT void OG_API OgCrDestoryUniversalRegistrar(OG_CR_UNIVERSAL_REGISTRAR *pur);
    OG_EXPORT OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *OgCrCreateUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR *pur);
    OG_EXPORT void *OG_API OgCrUniversalRegistrarIteratorNext(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri);
    OG_EXPORT void OG_API OgCrDestoryUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri);
    OG_EXPORT PTR_PROGRAM_MODULE OG_API OgCrGetProgramModulePointerByRegistrerdName(const char *pszRegisteredName);
    OG_EXPORT void *OG_API OgCrGetProgramModuleAdditionalData(PTR_PROGRAM_MODULE pModule);
    OG_EXPORT OG_ALWAYS_INLINE void OG_API OgCrPrintStackTrace();
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
    /**
     * @brief 获取线程局部存储结构指针
     * @return OG_CR_THREAD_LOCAL_STORAGE_STRUCT* TLS结构指针
     */
    OG_EXPORT OG_CR_THREAD_LOCAL_STORAGE_STRUCT *OG_API OgCrGetTLSStruct(void);

/* TLS 访问宏 */
#define OG_ERRNO (OgCrGetTLSStruct()->ecErrno)
#define OG_ERROR_MESSAGE (OgCrGetTLSStruct()->szAdditionalErrorMessage)
#define OG_ERROR_RECOVERABLE (OgCrGetTLSStruct()->bIsRecoverableException)

    /**
     * @brief 初始化线程局部存储
     * @param ufInitFlag 初始化标志
     * @return BOOL_T 成功返回 TRUE
     */
    OG_INTERNAL BOOL_T OG_API ogCrPvInitTSL();

    /**
     * @brief 释放线程局部存储
     * @return BOOL_T 成功返回 TRUE
     */
    OG_INTERNAL BOOL_T OG_API ogCrPvFreeTSL(void);

    /**
     * @brief 设置可恢复错误
     * @param ec 错误代码
     */
    OG_EXPORT void OG_API OgCrSetRecoverableError(OG_ERROR_T ec);

    /**
     * @brief 设置不可恢复错误
     * @param ec 错误代码
     */
    OG_EXPORT OG_NORERETURN void OG_API OgCrSetIrreversibleError(OG_ERROR_T ec);

    /**
     * @brief 格式化错误消息
     * @param code 错误代码
     * @param pszBuffer 输出缓冲区
     * @param uLengthOfBuffer 缓冲区长度
     */
    OG_EXPORT void OG_API OgCrFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer);

    /**
     * @brief 获取字符缓冲区
     * @return char* 字符缓冲区指针
     */
    OG_EXPORT char *OG_API OgCrGetCharBuffer(void);
    OG_EXPORT void OG_API OgCrSetErrorHandler(OG_CR_EXCEPTION_HANDLER_FUNCTION_T pfnHandler);
#define OG_CHAR_BUFFER OgCrGetCharBuffer()

        /**
         * @brief 初始化模块注册器
         * @return BOOL_T 成功返回 TRUE
         */
        OG_INTERNAL BOOL_T OG_API ogCrPvInitModuleRegistrar(void);

    /**
     * @brief 销毁模块注册器
     * @return BOOL_T 成功返回 TRUE
     */
    OG_INTERNAL BOOL_T OG_API crDestroyModuleRegistrar(void);

    /**
     * @brief 通过命名空间获取程序模块指针
     * @param uNamespace 模块命名空间
     * @return PTR_PROGRAM_MODULE 模块指针
     */
    OG_EXPORT PTR_PROGRAM_MODULE OG_API OgCrGetProgramModulePointerByNamespace(OG_MODULE_NAMESPACE_T uNamespace);

    /**
     * @brief 创建程序静态变量容器
     * @return OG_CR_UNIVERSAL_REGISTRAR* 通用注册器指针
     */
    OG_INTERNAL OG_CR_UNIVERSAL_REGISTRAR *OG_API ogCrCreateProgramStaticVariableContainer();

    /**
     * @brief 初始化核心组件
     * @return BOOL_T 成功返回 TRUE
     */
    OG_EXPORT BOOL_T OG_API OgCrInit();

    /* ============================================================================
     * 内联辅助函数
     * ============================================================================ */

    /**
     * @brief 如果值为NULL则设置错误
     * @param pvValue 要检查的值
     * @param uError 错误代码
     * @return void* 返回原值
     */
    inline void *OG_API OG_ALWAYS_INLINE OgCrSetErrorIfValueIsNULL(void *pvValue, OG_ERROR_T uError)
    {
        if (!pvValue)
        {
            OgCrSetRecoverableError(uError);
        }
        return pvValue;
    }

    /**
     * @brief 如果值为FALSE则设置错误
     * @param bValue 要检查的值
     * @param uError 错误代码
     * @return BOOL_T 返回原值
     */
    inline BOOL_T OG_API OG_ALWAYS_INLINE OgCrSetErrorIfValueIsFalse(BOOL_T bValue, OG_ERROR_T uError)
    {
        if (!bValue)
        {
            OgCrSetRecoverableError(uError);
        }
        return bValue;
    }

#ifdef __cplusplus
}
#endif

#endif /* OPEN_GAME_PRIVATE_H */
