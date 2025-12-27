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
 * @return OG_BOOL_T 返回TRUE时错误，设置ERRNO
 * @param ufInitFlag 默认为NULL,保留
 */
OG_EXTERN OG_BOOL_T OG_CDECL OgInit(uint64_t ufInitFlag);
/**
 * @brief 推出OpenStg
 * 
 * @note 仅在Posix中会释放TLS结构
 * @param ufQuitFlag 默认为NULL,保留
 * @return OgBoolean 返回TRUE时错误
 */
OG_EXTERN OG_BOOL_T OG_CDECL OgQuit();

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
 * @sa OgCreateElectromagneticDotTimer
 * @sa OgDestoryElectromagneticDotTimer
 * @sa OgElectromagneticDotTimerPullTask
 * @sa OgElectromagneticDotTimerSkipATimeStamp
 * @sa OgRefreshElectromagneticDotTimer
 */
typedef struct OG_ELECTROMAGNETIC_DOT_TIMER_ OG_ELECTROMAGNETIC_DOT_TIMER;
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
OG_EXTERN OG_ELECTROMAGNETIC_DOT_TIMER*OG_CDECL OgCreateElectromagneticDotTimer(int16_t iDotFrequency);
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
 * @brief 获取TLS(线程局部存储)结构的指针
 *
 * 不应该为NULL
 * 
 * @note 在POSIX环境中，若获取的值为NULL，则会自动分配内存
 * @note 在Windows中，未使用Pthreads实现，使用了原生DllMain()实现
 * @return OgTHREAD_LOCAL_STORAGE_STRUCT* 线程局部存储结构的指针 
 */
OG_EXTERN OG_THREAD_LOCAL_STORAGE_STRUCT* OG_CDECL OgGetTLSStruct(void);
#define OG_ERRNO (OgGetTLSStruct()->ecErrno)                     ///< 线程独立的Errno字段
#define OG_ERROR_MESSAGE (OgGetTLSStruct()->pszErrorMessage)     ///< 线程独立的ErrorMessage字段，长度原则上不长过 OPEN_STG_ERROR_MESSAGE_MAX_LENGTH-1

// NOTE: 改动时手动更改OgRegisteredProgramModule()函数
/**
 * @brief 注册模块时的参数
 */
typedef struct TagPROGRAM_MODULE
{
    int64_t iSize;                                 ///< (REQUIRED)版本控制，总应该初始化为sizeof(OgPROGRAM_MODULE)
    const char *pszModuleDisplayName;               ///< 输入，模块显示名称，如果为NULL，则会被设置为 in_pszRegisteredName
    union {
        const char *pszModuleRegisteredName;        ///< (REQUIRED)输入，注册名称，必须是唯一的，等同与 in_pszRegisteredId
        const char *pszModuleRegisteredId;          ///< 注册ID，必须是唯一的，等同与 in_pszRegisteredName
        intptr_t iPlaceholder;                      ///< 这个字段为什么会有用？😄️
    };
    OG_FORMAT_ERROR_MESSAGE_FUNCTION_T pfGetErrorMessage;    ///< (REQUIRED)输入，获取错误码对应的字符串描述函数
    void* pvAdditionalData;                         ///< 模块额外信息
    OG_MODULE_REGISTERED_FLAG_T ufModuleRegisteredFlag;    ///< 输入，位志符
    OG_ERROR_NAMESPACE_T uModuleNamespace;                      ///< 当 in_ufModuleRegisteredFlag 已设置，则不变，否则将设置为模块句柄
} OG_PROGRAM_MODULE;
/**
 * @brief 向程序注册模块
 * 
 * @param mod (必须非NULL)注册模块
 * @return OgBoolean 错误时返回false
 * 
 */
OG_EXTERN OG_BOOL_T OG_CDECL OgRegisteredProgramModule(const OG_PROGRAM_MODULE* mod);
/**
 * @brief 将错误码转化为字符串
 * 
 * @param code 错误码
 * @param pszBuffer 输出字符串缓冲区
 * @param uLengthOfBuffer 缓冲区的长度
 * @return void 
 */
OG_EXTERN void OG_CDECL OgCrGetErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer,uint64_t uLengthOfBuffer);
#ifdef __cplusplus
}
#endif
#endif
