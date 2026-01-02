/**
 * @file og_interface.h
 * @author IceThorn
 * @version Ciallo
 * @date 2025-11-22
 */
#include <stddef.h>
#include <stdint.h>
#include "OpenStgDefine.h"

#ifndef OPEN_GAME_H
#define OPEN_GAME_H 1


#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @brief 初始化OpenStg
 * 
 * @return BOOL_T 返回FALSE时错误，设置ERRNO
 * @param ufInitFlag 默认为NULL,保留
 */
OG_EXTERN BOOL_T OG_CDECL OgInit(uint64_t ufInitFlag);
/**
 * @brief 推出OpenStg
 * 
 * @note 仅在Posix中会释放TLS结构
 * @param ufQuitFlag 默认为NULL,保留
 * @return OgBoolean 返回FALSE时错误
 */
OG_EXTERN BOOL_T OG_CDECL OgQuit();

/**
 * @brief 物理课的杀人魔
 *
 * 一个神奇的计时器，内部维护着一个任务列表，每秒往列表中塞iFrequency个任务
 * 用于控制1秒内的计算次数，拥有较高的精度
 * 该Timer的实现与平台类型高度相关，故隐藏实现
 * 调用OgCreateElectromagneticDotTimer()创建计时器
 * 调用OgElectromagneticDotTimerPullTask()把陈年老账拉起来鞭尸(计算队列中的任务数)，
 * 调用OgElectromagneticDotTimerSkipATimeStamp()则等待到下一个加入队列，并清空队列
 * 调用OgRefreshElectromagneticDotTimer()重置计时器
 * 调用OgDestoryElectromagneticDotTimer()销毁计时器
 *
 * @note 本计时器设计时仅考虑了单线程场景
 * @since 0.1.0
 * @anchor IceThorn
 * @date 2025/11/23
 * @sa 
 * @sa OgDestoryElectromagneticDotTimer
 * @sa OgElectromagneticDotTimerPullTask
 * @sa OgElectromagneticDotTimerSkipATimeStamp
 * @sa OgRefreshElectromagneticDotTimer
 */
typedef struct TagOG_ELECTROMAGNETIC_DOT_TIMER OG_ELECTROMAGNETIC_DOT_TIMER;
/**
 * @brief 创建“电磁打点计时器”
 * 该函数会且仅会分配内存和写入时间表，所以想要开始计时功能请调用
 * OgRefreshElectromagneticDotTimer()函数
 *
 * @note 该函数应与OgDestoryElectromagneticDotTimer()函数成对调用
 * @sa OgRefreshElectromagneticDotTimer
 * @sa OgDestoryElectromagneticDotTimer
 * @param iDotFrequency 频率，即一秒内任务数，值<1时无效
 * @return OG_ELECTROMAGNETIC_DOT_TIMER* 参数无效时返回NULL
 */
OG_EXTERN OG_ELECTROMAGNETIC_DOT_TIMER* OG_CDECL OgCreateElectromagneticDotTimer(int16_t iDotFrequency);
/**
 * @brief 销毁“电磁打点计时器”
 * @note 该函数应与OgCreateElectromagneticDotTimer()函数成对调用
 * @sa OgCreateElectromagneticDotTimer
 * @param[in] pEdt 
 * @return void
 */
OG_EXTERN void OG_CDECL OgDestoryElectromagneticDotTimer(OG_ELECTROMAGNETIC_DOT_TIMER *pEdt);
/**
 * @brief 计算队列中的任务数
 * @param[in] pEdt 
 * @return int64_t  
 */
OG_EXTERN int64_t OG_CDECL OgElectromagneticDotTimerPullTask(OG_ELECTROMAGNETIC_DOT_TIMER* pEdt);
/**
 * @brief 等待直到下一个任务加入队列，并清空队列
 * @param[in] pEdt 
 * @return void 
 */
OG_EXTERN void OG_CDECL OgElectromagneticDotTimerSkipATimeStamp(OG_ELECTROMAGNETIC_DOT_TIMER* pEdt);
/**
 * @brief 初始化并清空队列
 * @param[in] pEdt 
 * @return void 
 */
OG_EXTERN void OG_CDECL OgRefreshElectromagneticDotTimer(OG_ELECTROMAGNETIC_DOT_TIMER *pEdt);
/**
 * @brief 初始化Core部分组件
 *
 * 初始化TLS结构，模块注册器结构
 * @return BOOL_T 成功时返回TRUE，否则返回FALSE
 */
OG_EXTERN BOOL_T OG_CDECL OgCrInit();
/**
 * @brief 获取TLS(线程局部存储)结构的指针
 *
 * 不应该为NULL
 * 
 * @note 在POSIX环境中，若获取的值为NULL，则会自动分配内存
 * @note 在Windows中，未使用Pthreads实现，使用了原生DllMain()实现
 * @return OG_THREAD_LOCAL_STORAGE_STRUCT* 线程局部存储结构的指针 
 */
OG_EXTERN OG_THREAD_LOCAL_STORAGE_STRUCT* OG_CDECL OgCrGetTLSStruct(void);
#define OG_ERRNO (OgCrGetTLSStruct()->ecErrno)                              ///< 线程独立的Errno字段
#define OG_ERROR_MESSAGE (OgCrGetTLSStruct()->pszErrorMessage)              ///< 线程独立的ErrorMessage字段
#define OG_ERROR_RECOVERABLE (OgCrGetTLSStruct()->bIsRecoverableException)  ///< 线程独立的ErrorReconverable字段

// NOTE: 改动时手动更改OgCrRegisterProgramModule()函数
/**
 * @brief 注册模块时的参数
 */
typedef struct TagCrPROGRAM_MODULE
{
    int64_t iSize;                                          ///< (REQUIRED)版本控制，总应该初始化为sizeof(OgPROGRAM_MODULE)
    OG_MODULE_REGISTERED_FLAG_T ufModuleRegisteredFlag;     ///< 输入，位志符
    const char *pszModuleDisplayName;                       ///< 输入，模块显示名称，如果为NULL，则会被设置为 pszRegisteredName
    union {
        const char *pszModuleRegisteredName;                ///< (REQUIRED)输入，注册名称，必须是唯一的，等同与 pszRegisteredId
        const char *pszModuleRegisteredId;                  ///< 注册ID，必须是唯一的，等同与 pszRegisteredName
        intptr_t iPlaceholder;                              ///< 这个字段为什么会有用？😄️
    };
    OG_FORMAT_ERROR_MESSAGE_FUNCTION_T pfFormatErrorMessage;   ///< (REQUIRED)输入，获取错误码对应的字符串描述函数
    void *pvAdditionalData;                                 ///< 模块额外信息
    const char **rgpszDependencyRegistraredName;            ///< 输入，指向一个字符串数组，包涵依赖项的注册名
    uint32_t uCountOfDependencies;                          ///< 输入，指示rgpszDependencyRegistraredName成员的个数
    OG_MODULE_NAMESPACE_T ModuleNamespace;                  ///< 输出，设置为模块空间名称

} OG_CR_PROGRAM_MODULE;
/**
 * @brief 向程序注册模块
 * @param mod (必须非NULL)注册模块
 * @return OgBoolean 错误时返回 FALSE
 */
OG_EXTERN BOOL_T OG_CDECL OgCrRegisterProgramModule(const OG_CR_PROGRAM_MODULE *mod,uint32_t *puNamespaceOutput); 
/**
 * @brief 注销指定名称的模块
 * @note 用于热重载，仅注销模块，不卸载对应动态库
 * @param[in] pszModuleRegisteredName 
 * @return OG_EXTERN 
 */
OG_EXTERN BOOL_T OG_CDECL OgCrUnregisterProgramModule(const char* pszModuleRegisteredName); 
/**
 * @brief 模块迭代器，检索已注册的模块
 * @note 模块成员不公开，线程不安全
 */
typedef struct TagOgCrMODULE_ITREATOR OG_CR_MODULE_ITERATOR;
/**
 * @brief 获取全局模块注册器的迭代器
 * @return OG_CR_MODULE_ITERATOR* 失败时返回NULL，否则返回一个可用指针
 */
OG_EXTERN OG_CR_MODULE_ITERATOR* OG_CDECL OgCrCreateModuleRegistrarIterator();
/**
 * @brief 将迭代器中的指针移动至下一个模块，并返回其指向的模块内容
 * @note 不会返回模块的rgpszDependencyRegistraredName和uCountOfDependencies成员
 * @param piter 创建的迭代器
 * @param pmod 返回的模块内容
 * @return BOOL_T 成功时返回TRUE，无下一个模块时返回FALSE
 */
OG_EXTERN BOOL_T OG_CDECL OgCrModuleRegistrarIteratorNext(OG_CR_MODULE_ITERATOR* piter,OG_CR_PROGRAM_MODULE* pmod);
/**
 * @brief 
 * 
 * @param piter 
 * @return OG_EXTERN 
 */
OG_EXTERN void OG_CDECL OgCrDestoryModuleRegistrarIterator(OG_CR_MODULE_ITERATOR* piter);
/**
 * @brief 将错误码转化为字符串
 * 
 * @param code 错误码
 * @param pszBuffer 输出字符串缓冲区
 * @param uLengthOfBuffer 缓冲区的长度
 * @return void 
 */
OG_EXTERN void OG_CDECL OgCrFormatErrorMessage(
    OG_ERROR_CODE_T code, 
    char *pszBuffer,
    uint64_t uLengthOfBuffer
);
/**
 * @brief 通用注册项容器(通用注册器)
 *
 * @note 内部的主要结构是一个目标类型数组和一个布尔数组
 */
typedef struct TagOgCrUNIVERSAL_REGISTRAR OG_CR_UNIVERSAL_REGISTRAR;
typedef struct TagUNIVERSAL_REGISTRAR_INFORMATION
{
    int64_t iSize;
    OG_CR_UNIVERSAL_REGISTRAR_FLAG_T ufCreateFlags;
    uint32_t uItemStructureSize;
    uint32_t uPreAllocatedCount;
    const char* pszStructureName;
    OG_DESTORY_MEMBER_FUNCTION_T pfDestoryMemberFunction;
}OG_CR_UNIVERSAL_REGISTRAR_INFORMATION;
/**
 * @brief 创建通用注册器
 * 
 * @param puri 必须不为NULL 
 * @return OG_BS_UNIVERSAL_REGISTRAR* 创建成功的通用注册器，返回NULL时设置错误
 */
OG_EXTERN OG_CR_UNIVERSAL_REGISTRAR* OG_CDECL OgCrCreateUniversalRegistrar(
    const OG_CR_UNIVERSAL_REGISTRAR_INFORMATION *puri
);
/**
 * @brief 在注册器中预订(预分配)指定数量的空位
 * 
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @param[in] uReserveCount 预订空位数
 * @return BOOL_T 成功时返回TRUE，错误时返回FALSE
 */
OG_EXTERN BOOL_T OG_CDECL OgCrUniversalRegistrarReserveItems(
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
OG_EXTERN int64_t OG_CDECL OgCrUniversalRegistrarAllocateItem(OG_CR_UNIVERSAL_REGISTRAR *pur,void**pOutput);
/**
 * @brief 分配预分配的项
 * 
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @param[in] uPreAllocatedIndex 预分配项的索引
 * @param[out] pOutput 返回分配的指针
 * @return int64_t 成功是返回非负数(即该对象在容器的索引)，错误时返回负数
 */
OG_EXTERN int64_t OG_CDECL OgCrUniversalRegistrarAllocatePreallocatedItem(
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
OG_EXTERN void* OG_CDECL OgCrUniversalRegistrarGetItem(OG_CR_UNIVERSAL_REGISTRAR *pur,uint32_t uIndex);
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
OG_EXTERN BOOL_T OG_CDECL OgCrUniversalRegistrarFreeItem(OG_CR_UNIVERSAL_REGISTRAR *pur,uint32_t uIndex);
/**
 * @brief 销毁通用注册器
 * 
 * @param[in] pur 通用注册器指针，必须不为NULL
 * @return BOOL_T 成功时返回TRUE，错误时返回FALSE
 */
OG_EXTERN void OG_CDECL OgCrDestoryUniversalRegistrar(OG_CR_UNIVERSAL_REGISTRAR *pur);
typedef struct TagOgCrUNIVERSAL_REGISTRAR_ITERATOR OG_CR_UNIVERSAL_REGISTRAR_ITERATOR;
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
OG_EXTERN void* OgCrUniversalRegistrarIteratorNext(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri);
/**
 * @brief 释放通用注册器迭代器
 * 
 * @param[in] puri 通用注册器指针，必须不为NULL
 * @return void 
 */
OG_EXTERN void OgCrDestoryUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri);
#ifdef __cplusplus
}
#endif
#endif
