/**
 * @file og_interface.h
 * @author IceThorn
 * @version Ciallo
 * @date 2025-11-22
 */
#include <stddef.h>
#include <stdint.h>
#include <OpenStg/OpenStgDefine.h>

#ifndef OPEN_GAME_H
#define OPEN_GAME_H 1


#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @brief 创建“电磁打点计时器”
 * 该函数会且仅会分配内存和写入时间表，所以想要开始计时功能请调用
 * OgCrRefreshElectromagneticDotTimer()函数
 *
 * @note 该函数应与OgCrDestoryElectromagneticDotTimer()函数成对调用
 * @sa OgCrRefreshElectromagneticDotTimer
 * @sa OgCrDestoryElectromagneticDotTimer
 * @param iDotFrequency 频率，即一秒内任务数，值<1时无效
 * @return OG_CR_ELECTROMAGNETIC_DOT_TIMER* 参数无效时返回NULL
 */
OG_EXTERN OG_CR_ELECTROMAGNETIC_DOT_TIMER* OG_API OgCrCreateElectromagneticDotTimer(int8_t iDotFrequency);
/**
 * @brief 销毁“电磁打点计时器”
 * @note 该函数应与OgCrCreateElectromagneticDotTimer()函数成对调用
 * @sa OgCrCreateElectromagneticDotTimer
 * @param[in] pEdt
 * @return void
 */
OG_EXTERN void OG_API OgCrDestoryElectromagneticDotTimer(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt);
/**
 * @brief 计算队列中的任务数
 * @param[in] pEdt
 * @return int64_t
 */
OG_EXTERN int64_t OG_API OgCrElectromagneticDotTimerPullTask(OG_CR_ELECTROMAGNETIC_DOT_TIMER* pEdt);
/**
 * @brief 等待直到下一个任务加入队列，并清空队列
 * @param[in] pEdt
 * @return void
 */
OG_EXTERN void OG_API OgCrElectromagneticDotTimerSkipATimeStamp(OG_CR_ELECTROMAGNETIC_DOT_TIMER* pEdt);
/**
 * @brief 初始化并清空队列
 * @param[in] pEdt
 * @return void
 */
OG_EXTERN void OG_API OgCrRefreshElectromagneticDotTimer(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt);
/**
 * @brief 初始化Core部分组件
 *
 * 初始化TLS结构，模块注册器结构
 * @return BOOL_T 成功时返回TRUE，否则返回FALSE
 */
OG_EXTERN BOOL_T OG_API OgCrInit();
/**
 * @brief 获取TLS(线程局部存储)结构的指针
 *
 * 不应该为NULL
 *
 * @note 在POSIX环境中，若获取的值为NULL，则会自动分配内存
 * @note 在Windows中，未使用Pthreads实现，使用了原生DllMain()实现
 * @return OG_CR_THREAD_LOCAL_STORAGE_STRUCT* 线程局部存储结构的指针
 */
OG_EXTERN const OG_CR_THREAD_LOCAL_STORAGE_STRUCT* OG_API OgCrGetTLSStruct(void);
#define OG_ERRNO (OgCrGetTLSStruct()->ecErrno)                              ///< 线程独立的Errno字段
#define OG_ERROR_MESSAGE (OgCrGetTLSStruct()->pszErrorMessage)              ///< 线程独立的ErrorMessage字段
#define OG_ERROR_RECOVERABLE (OgCrGetTLSStruct()->bIsRecoverableException)  ///< 线程独立的ErrorReconverable字段
/**
 * @brief 返回一个长度为 OPEN_STG_CONST_UNIVERSAL_BUFFER_LENGTH 的BYTE缓冲区
 * @note 即OG_CR_THREAD_LOCAL_STORAGE_STRUCT结构的szUniversalBuffer可读写字段
 */
OG_EXTERN char* OG_API OgCrGetCharBuffer(void);
#define OG_CHAR_BUFFER OgCrGetCharBuffer()
/**
 * @brief 创建通用注册器
 *
 * @param puri 必须不为NULL
 * @return OG_BS_UNIVERSAL_REGISTRAR* 创建成功的通用注册器，返回NULL时设置错误
 */
OG_EXTERN OG_CR_UNIVERSAL_REGISTRAR* OG_API OgCrCreateUniversalRegistrar(
    const OG_CR_UNIVERSAL_REGISTRAR_INFORMATION *puri
);
/**
 * @brief 在注册器中预订(预分配)指定数量的空位
 *
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @param[in] uReserveCount 预订空位数
 * @return BOOL_T 成功时返回TRUE，错误时返回FALSE
 */
OG_EXTERN BOOL_T OG_API OgCrUniversalRegistrarReserveItems(
    OG_CR_UNIVERSAL_REGISTRAR *pur,
    uint32_t uReserveCount
);
/**
 * @brief 在通用注册器中分配一个新项
 *
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @param[out] pOutput 返回分配的指针
 * @return int64_t 成功是返回非负数(即该对象在容器的索引)，错误时返回负数
 */
OG_EXTERN int64_t OG_API OgCrUniversalRegistrarAllocateItem(OG_CR_UNIVERSAL_REGISTRAR *pur,void**pOutput);
/**
 * @brief 分配预分配的项
 *
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @param[in] uPreAllocatedIndex 预分配项的索引
 * @param[out] pOutput 返回分配的指针
 * @return int64_t 成功是返回非负数(即该对象在容器的索引)，错误时返回负数
 */
OG_EXTERN int64_t OG_API OgCrUniversalRegistrarAllocatePreallocatedItem(
    OG_CR_UNIVERSAL_REGISTRAR *pur,
    uint32_t uPreAllocatedIndex,
    void** pOutput
);
/**
 * @brief 获取通用注册器中指定索引的项
 *
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @param[in] uIndex 项的索引
 * @return void* 成功时返回项的指针，失败时返回NULL，索引无效或索引无内容返回NULL
 */
OG_EXTERN void* OG_API OgCrUniversalRegistrarGetItem(OG_CR_UNIVERSAL_REGISTRAR *pur,uint64_t uIndex);
/**
 * @brief 释放通用注册器中指定索引的项
 *
 * 如果创建时pfDestoryMemberFunction不为NULL则调用
 * 受OPEN_STG_FLAG_UNIVERSAL_REGISTRAR_NOT_INITIALIZED位志符影响
 *
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @param[in] uIndex 要释放的项的索引
 * @return BOOL_T 当参数pur为NULL时返回TRUE，uIndex对应的位置不存在返回TRUE，正常时返回TRUE，否则返回FALSE
 */
OG_EXTERN BOOL_T OG_API OgCrUniversalRegistrarFreeItem(OG_CR_UNIVERSAL_REGISTRAR *pur,uint64_t uIndex);
/**
 * @brief 获取通用注册器中的已分配内存的结构数
 *
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @return int64_t 当参数pur为NULL时返回-1，否则返回已分配内存的结构数
 */
OG_EXTERN int64_t OG_API OgCrUniversalRegistrarGetReservedItemCount(OG_CR_UNIVERSAL_REGISTRAR *pur);
/**
 * @brief 获取通用注册器中的已分配的结构数
 *
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @return int64_t 当参数pur为NULL时返回-1，否则返回已分配内存的结构数
 */
OG_EXTERN int64_t OG_API OgCrUniversalRegistrarGetAllocatedItemCount(OG_CR_UNIVERSAL_REGISTRAR *pur);
/**
 * @brief 销毁通用注册器
 *
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @return BOOL_T 成功时返回TRUE，错误时返回FALSE
 */
OG_EXTERN void OG_API OgCrDestoryUniversalRegistrar(OG_CR_UNIVERSAL_REGISTRAR *pur);
/**
 * @brief 创建通用注册器迭代器
 *
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @return OG_CR_UNIVERSAL_REGISTRAR_ITERATOR* 成功时返回迭代器指针，失败时返回NULL
 */
OG_EXTERN OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *OgCrCreateUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR *pur);
/**
 * @brief 获取该项，移动通用注册器迭代器到下一项
 * @code {.c}
 * OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *uri=NULL;
 * void *p = NULL;
 * uri = OgCrCreateUniversalRegistrarIterator(...);
 * while((p = OgCrUniversalRegistrarIteratorNext(uri)) != NULL)
 * {
 *     ...
 * }
 * OgCrDestoryUniversalRegistrarIterator(uri);
 * @endcode
 *
 *
 * @param[in] puri 通用注册器指针，必须不为NULL
 * @return void* 输出当前项的指针，错误时返回NULL
 */
OG_EXTERN void *OG_API OgCrUniversalRegistrarIteratorNext(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri);
/**
 * @brief 释放通用注册器迭代器
 *
 * @param[in] puri 通用注册器指针，必须不为NULL
 * @return void
 */
OG_EXTERN void OG_API OgCrDestoryUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri);
/**
 * @brief 向程序注册模块
 * @param mod (必须非NULL)注册模块
 * @return OgBoolean 错误时返回 FALSE
 */
OG_EXTERN BOOL_T OG_API OgCrRegisterProgramModule(const OG_CR_PROGRAM_MODULE *mod,uint32_t *puNamespaceOutput);
/**
 * @brief 注销指定名称的模块
 * @note 用于热重载，仅注销模块，不卸载对应动态库
 * @param[in] pszModuleRegisteredName
 * @return OG_EXTERN
 */
OG_EXTERN BOOL_T OG_API OgCrUnregisterProgramModule(const char* pszModuleRegisteredName);

/**
 * @brief 获取全局模块注册器的迭代器
 * @return OG_CR_MODULE_ITERATOR* 失败时返回NULL，否则返回一个可用指针
 */
OG_EXTERN OG_CR_PROGRAM_MODULE_ITERATOR* OG_API OgCrCreateProgramModuleRegistrarIterator();
/**
 * @brief 将迭代器中的指针移动至下一个模块，并返回其指向的模块内容
 * @note 不会返回模块的rgpszDependencyRegistraredName和uCountOfDependencies成员
 * @param piter 创建的迭代器
 * @param pmod 返回的模块内容
 * @return BOOL_T 成功时返回TRUE，无下一个模块时返回FALSE
 */
OG_EXTERN BOOL_T OG_API OgCrProgramModuleRegistrarIteratorNext(OG_CR_PROGRAM_MODULE_ITERATOR* piter,OG_CR_PROGRAM_MODULE* pmod);
/**
 * @brief 销毁模块注册器迭代器
 * @param piter 要销毁的迭代器
 */
OG_EXTERN void OG_API OgCrDestoryProgramModuleRegistrarIterator(OG_CR_PROGRAM_MODULE_ITERATOR* piter);
/**
 * @brief 通过空间名称获取模块指针
 *
 * @param uNamespace 目标模块空间名称
 * @return PTR_PROGRAM_MODULE 目标模块指针
 */
OG_EXTERN PTR_PROGRAM_MODULE OG_API OgCrGetProgramModulePointerByNamespace(OG_MODULE_NAMESPACE_T uNamespace);
/**
 * @brief 通过模块注册名获取模块指针
 *
 * @param pszRegisteredName 模块注册名
 * @return PTR_PROGRAM_MODULE 目标模块指针
 */
OG_EXTERN PTR_PROGRAM_MODULE OG_API OgCrGetProgramModulePointerByRegistrerdName(const char* pszRegisteredName);
/**
 * @brief 通过模块指针获取模块附加数据
 *
 * @param pModule 目标模块指针
 * @return void* 目标模块附加数据
 */
OG_EXTERN void * OG_API OgCrGetProgramModuleAdditionalData(PTR_PROGRAM_MODULE pModule);
/**
 * @brief 将错误码转化为字符串
 *
 * @param code 错误码
 * @param pszBuffer 输出字符串缓冲区
 * @param uLengthOfBuffer 缓冲区的长度
 * @return void
 */
OG_EXTERN void OG_API OgCrFormatErrorMessage(
    OG_ERROR_CODE_T code,
    char *pszBuffer,
    uint64_t uLengthOfBuffer
);
/**
 * @brief 将错误码转化为字符串
 *
 * @note 格式化函数由模块提供
 * @param eError 错误码
 * @param pszBuffer 输出字符串缓冲区
 * @param uLengthOfBuffer 缓冲区的长度
 * @return void
 */
OG_EXTERN void OG_API OgFormatErrorMessage(
    OG_ERROR_T eError,
    char *pszBuffer,
    uint64_t uLengthOfBuffer
);
/**
 * @brief 设置OG_ERRNO和OG_ERROR_RECOVERABLE
 *
 * @param ec
 */
OG_EXPORT void OG_API OgCrSetRecoverableError(OG_ERROR_T ec);
/**
 * @brief 设置不可恢复错误
 * @param ec 错误代码
 */
OG_EXPORT OG_NORERETURN void OG_API OgCrSetIrreversibleError(OG_ERROR_T ec);
/**
 * @brief 设置可恢复错误的错误码和消息
 * 
 * @param pszMessage 
 */
OG_EXPORT void OG_API OgCrSetRecoverableErrorAndMessage(OG_ERROR_T ec,const char *pszMessage);
/**
 * @brief 设置异常处理器
 *
 * @param pfnHandler
 * @note 在OgCrSetRecoverableError和OgCrSetIrreversibleError被调用时调用
 */
OG_EXTERN void OG_API OgCrSetErrorHandler(
    OG_CR_EXCEPTION_HANDLER_FUNCTION_T pfnHandler
);
/**
 * @brief 设置错误uError当传入值pvValue是NULL，并返回传入值pvValue
 * @note 不导入Rust
 *
 * @param pvValue 传入值
 * @param uError 错误值
 * @return void* 将返回传入值
 */
inline void *OG_API OG_ALWAYS_INLINE OgCrSetErrorIfValueIsNULL(void* pvValue,OG_ERROR_T uError)
{
    if(pvValue == NULL)
    {
        OgCrSetRecoverableError(uError);
    }
    return pvValue;
}
/**
 * @brief 设置错误uError当传入值bValue是NULL，并返回传入值bValue
 * @note 不导入Rust
 *
 * @param bValue 传入值
 * @param uError 错误值
 * @return BOOL_T 将返回传入值
 */
inline BOOL_T OG_API OG_ALWAYS_INLINE OgCrSetErrorIfValueIsFalse(BOOL_T bValue,OG_ERROR_T uError)
{
    if(!bValue)
    {
        OgCrSetRecoverableError(uError);
    }
    return bValue;
}
/**
 * @brief 打印调用堆栈
 */
OG_EXTERN OG_ALWAYS_INLINE void OG_API OgCrPrintStackTrace();
/**
 * @brief 当传入指针为NULL时打印错误信息并退出程序，否则返回传入指针
 */
OG_EXTERN void *OG_API OgCrNoExceptPtrVa(void *p);
/**
 * @brief 当传入指针p为NULL时打印错误信息并退出程序，否则返回传入指针p
 *
 * @note 不导入Rust
 *
 * @param p 传入指针
 * @param pszExpression (由宏填写)表达式
 * @param pszFunction (由宏填写)所在函数
 * @param pszFile (由宏填写)所在文件
 * @param uLine (由宏填写)所在行
 * @return void* 回传指针
 */
OG_EXTERN void *OG_API OgCrNoExceptPtrEx(
    void *p,
    const char *pszExpression,
    const char *pszFunction,
    const char *pszFile,
    uint64_t uLine
);
/**
 * @brief 当传入值为NULL时打印错误信息并退出程序，否则返回传入值
 */
OG_EXTERN BOOL_T OG_API OgCrNoExceptBooleanVa(BOOL_T b);
/**
 * @brief 当传入值并b为FALSE时打印错误信息并退出程序，否则返回传入值b
 *
 * @note 不导入Rust
 *
 * @param b 传入值
 * @param pszExpression (由宏填写)表达式
 * @param pszFunction (由宏填写)所在函数
 * @param pszFile (由宏填写)所在文件
 * @param uLine (由宏填写)所在行
 * @return void* 回传值
 */
OG_EXTERN BOOL_T OG_API OgCrNoExceptBooleanEx(
    BOOL_T b,
    const char *pszExpression,
    const char *pszFunction,
    const char *pszFile,
    uint64_t uLine
);
#if OPEN_STG_MACRO_IS_DEBUG
#define OgCrNoExceptPtr(p) OgCrNoExceptPtrEx((p), #p, OPEN_STG_MACRO_FUNCTION, __FILE__, __LINE__ + 1)
#define OgCrNoExceptBoolean(b) OgCrNoExceptBooleanEx((b), #b, OPEN_STG_MACRO_FUNCTION, __FILE__, __LINE__ + 1)
#else
#define OgCrNoExceptPtr(p) OgCrNoExceptPtrVa
#define OgCrNoExceptBoolean(b) OgCrNoExceptBooleanVa
#endif

#ifdef __cplusplus
}
#endif
#endif
