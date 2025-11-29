/**
 * @file og_interface.h
 * @author IceThorn
 * @brief
 * @version Ciallo
 * @date 2025-11-22
 *
 *
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
 * @brief 物理课的杀人魔
 *
 * 一个神奇的计时器，内部维护着一个任务列表，每秒往列表中塞iFrequency个任务
 * 用于控制1秒内的计算次数，拥有较高的精度
 * 该Timer的实现与平台类型高度相关，故隐藏实现
 * 调用OgElectromagneticDotTimerCreate()创建计时器
 * 调用OgElectromagneticDotTimerPullTask()把陈年老账拉起来鞭尸(计算队列中的任务数)，
 * 调用OgElectromagneticDotTimerSkipATimeStamp()则等待到下一个加入队列，并清空队列
 * 调用OgElectromagneticDotTimerRefresh()重置计时器
 * 调用OgElectromagneticDotTimerDestory()销毁计时器
 *
 * @note 本计时器设计时仅考虑了单线程场景
 * @since 0.1.0
 * @anchor IceThorn
 * @date 2025/11/23
 * @sa OgElectromagneticDotTimerCreate
 * @sa OgElectromagneticDotTimerDestory
 * @sa OgElectromagneticDotTimerPullTask
 * @sa OgElectromagneticDotTimerSkipATimeStamp
 * @sa OgElectromagneticDotTimerRefresh
 */
typedef struct OgELECTROMAGNETIC_DOT_TIMER_ OgELECTROMAGNETIC_DOT_TIMER;
/**
 * @brief 创建“电磁打点计时器”
 * 该函数会且仅会分配内存和写入时间表，所以想要开始计时功能请调用
 * OgElectromagneticDotTimerRefresh()函数
 *
 * @note 该函数应与OgElectromagneticDotTimerDestory()函数成对调用
 * @sa OgElectromagneticDotTimerRefresh
 * @sa OgElectromagneticDotTimerDestory
 * @param iFrequency 频率，即一秒内任务数，值<1时无效
 * @return OgELECTROMAGNETIC_DOT_TIMER* 参数无效时返回NULL
 */
OPEN_STG_EXTERN OPEN_STG_CDECL OgELECTROMAGNETIC_DOT_TIMER* OgElectromagneticDotTimerCreate(int16_t iFrequency);
/**
 * @brief 销毁“电磁打点计时器”
 * @note 该函数应与OgElectromagneticDotTimerCreate()函数成对调用
 * @sa OgElectromagneticDotTimerCreate
 * @param[in] pEdt 
 * @return void
 */
OPEN_STG_EXTERN OPEN_STG_CDECL void OgElectromagneticDotTimerDestory(OgELECTROMAGNETIC_DOT_TIMER *pEdt);
/**
 * @brief 计算队列中的任务数
 * @param[in] pEdt 
 * @return int64_t  
 */
OPEN_STG_EXTERN OPEN_STG_CDECL int64_t OgElectromagneticDotTimerPullTask(OgELECTROMAGNETIC_DOT_TIMER* pEdt);
/**
 * @brief 等待直到下一个任务加入队列，并清空队列
 * @param[in] pEdt 
 * @return void 
 */
OPEN_STG_EXTERN OPEN_STG_CDECL void OgElectromagneticDotTimerSkipATimeStamp(OgELECTROMAGNETIC_DOT_TIMER* pEdt);
/**
 * @brief 初始化并清空队列
 * @param[in] pEdt 
 * @return void 
 */
OPEN_STG_EXTERN OPEN_STG_CDECL void OgElectromagneticDotTimerRefresh(OgELECTROMAGNETIC_DOT_TIMER *pEdt);
#ifdef __cplusplus
}
#endif
#endif
