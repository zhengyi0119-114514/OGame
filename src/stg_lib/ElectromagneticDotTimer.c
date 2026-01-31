#include "CloseStgCore.h"

#if defined WIN32 || WINDOWS32
#include <windows.h>
typedef struct TagOgCrELECTROMAGNETIC_DOT_TIMER
{
    LARGE_INTEGER *rgliDotTable;
    LARGE_INTEGER liProcessorFrequency;
    LARGE_INTEGER liStart;
    LARGE_INTEGER liLast;
    int8_t iDotFrequency;
} OG_CR_ELECTROMAGNETIC_DOT_TIMER;

OG_CR_ELECTROMAGNETIC_DOT_TIMER *OG_API OgCrCreateElectromagneticDotTimer(int8_t iDotFrequency)
{
    if (iDotFrequency < 1)
        return NULL;
    OG_CR_ELECTROMAGNETIC_DOT_TIMER *pedt = NULL;
    LARGE_INTEGER *rgliDotTable = NULL, liProcessorFrequency, liStart;
    // 分配并初始化内存
    pedt = (OG_CR_ELECTROMAGNETIC_DOT_TIMER *)malloc(sizeof(OG_CR_ELECTROMAGNETIC_DOT_TIMER));
    rgliDotTable = (LARGE_INTEGER *)calloc(iDotFrequency + 1, sizeof(LARGE_INTEGER)); // NOTE: 这里多分配一个对象
    if ((pedt == NULL) || (rgliDotTable == NULL))
    {
        free((void *)pedt);
        free((void *)rgliDotTable);
        return NULL;
    }
    ZeroMemory((void *)pedt, sizeof(OG_CR_ELECTROMAGNETIC_DOT_TIMER));
    // 取值
    QueryPerformanceFrequency(&liProcessorFrequency);
    QueryPerformanceCounter(&liStart);
    // 设置时间表
    for (uint16_t uIndex = 0; uIndex < iDotFrequency + 1; uIndex++)
    {
        rgliDotTable[uIndex].QuadPart = liProcessorFrequency.QuadPart * uIndex / iDotFrequency;
    }
    // 赋值
    pedt->rgliDotTable = rgliDotTable;
    pedt->liStart = liStart;
    pedt->liProcessorFrequency = liProcessorFrequency;
    pedt->liLast = liStart;
    pedt->iDotFrequency = iDotFrequency;
    return (pedt);
}
void OgCrDestoryElectromagneticDotTimer(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (pEdt)
    {
        if (pEdt->rgliDotTable)
            free((void *)pEdt->rgliDotTable);
        free((void *)pEdt);
    }
}
int64_t OgCrElectromagneticDotTimerPullTask(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (pEdt == NULL)
        return (0);
    int64_t iResult = 0;
    LARGE_INTEGER liCurrentTime;
    LARGE_INTEGER liTimeDifference, liRemainingPart;
    QueryPerformanceCounter(&liCurrentTime);
    liTimeDifference.QuadPart = liCurrentTime.QuadPart - pEdt->liLast.QuadPart;
    liRemainingPart.QuadPart = liTimeDifference.QuadPart % pEdt->liProcessorFrequency.QuadPart;
    iResult += liTimeDifference.QuadPart / pEdt->liProcessorFrequency.QuadPart * pEdt->iDotFrequency;
    iResult += liRemainingPart.QuadPart * pEdt->iDotFrequency / pEdt->liProcessorFrequency.QuadPart;
    return iResult;
}
void OgCrRefreshElectromagneticDotTimer(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (pEdt == NULL)
        return;
    LARGE_INTEGER liCurrentTime;
    QueryPerformanceCounter(&liCurrentTime);
    pEdt->liLast = liCurrentTime;
    pEdt->liStart = liCurrentTime;
}
void OgCrElectromagneticDotTimerSkipATimeStamp(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (pEdt == NULL)
        return;
    LARGE_INTEGER liTimeDifference;
    LARGE_INTEGER liCurrentTime;
    LARGE_INTEGER liTimeSleepTarget;
    LARGE_INTEGER liCache;
    DWORD dwMillisecondsToSleep;

    liTimeSleepTarget.QuadPart = UINT64_C(0);
    QueryPerformanceCounter(&liCurrentTime);
    liTimeDifference.QuadPart = liCurrentTime.QuadPart - pEdt->liStart.QuadPart;
    liTimeDifference.QuadPart %= pEdt->liProcessorFrequency.QuadPart;
    for (uint16_t uIndex = 0, uIndexMax = pEdt->iDotFrequency + 1; uIndex < uIndexMax; uIndex++)
    {
        if ((pEdt->rgliDotTable[uIndex].QuadPart) < liTimeDifference.QuadPart &&
            (liTimeDifference.QuadPart <= (liCache.QuadPart = pEdt->rgliDotTable[uIndex + 1].QuadPart)))
        {
            liTimeSleepTarget.QuadPart = liCache.QuadPart - liTimeDifference.QuadPart;
        }
    }
    liCache.QuadPart = liCurrentTime.QuadPart + liTimeSleepTarget.QuadPart;
    dwMillisecondsToSleep = liTimeSleepTarget.QuadPart * 1000 / pEdt->liProcessorFrequency.QuadPart;
    Sleep(dwMillisecondsToSleep);
    while (TRUE)
    {
        QueryPerformanceCounter(&liCache);
        if (liCache.QuadPart - liCurrentTime.QuadPart >= liTimeSleepTarget.QuadPart)
        {
            break;
        }
    }
    QueryPerformanceCounter(&liCurrentTime);
    pEdt->liLast = liCurrentTime;
}
#elif defined POSIX || defined __unix__ || defined __unix
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMBER_OF_NS_IN_PRE_SECOND ((int64_t)(1000000000))
typedef struct TagOgCrELECTROMAGNETIC_DOT_TIMER
{
    int64_t *piDotTable;
    struct timespec tsLast;
    struct timespec tsStart;
    int8_t iDotFrequency;
} OG_CR_ELECTROMAGNETIC_DOT_TIMER;
OG_PRIVATE OG_API inline void TimespecDifference(struct timespec *ptsSubtrahend, struct timespec *ptsReduction,
                                                   struct timespec *ptsOutput);
OG_PRIVATE OG_API inline int64_t TimespecToInt64(struct timespec *pts);
OG_PRIVATE OG_API inline struct timespec Int64ToTimespec(int64_t i);

int64_t TimespecToInt64(struct timespec *pts)
{
    return pts->tv_sec * NUMBER_OF_NS_IN_PRE_SECOND + pts->tv_nsec;
}
struct timespec Int64ToTimespec(int64_t i)
{
    struct timespec tsResult;
    tsResult.tv_sec = i / NUMBER_OF_NS_IN_PRE_SECOND;
    tsResult.tv_nsec = i % NUMBER_OF_NS_IN_PRE_SECOND;
    return tsResult;
}
void TimespecDifference(struct timespec *ptsSubtrahend, struct timespec *ptsReduction, struct timespec *ptsOutput)
{
    int64_t iSecondsDifference = ptsSubtrahend->tv_sec - ptsReduction->tv_sec;
    int64_t iNanoSecondDifference = ptsSubtrahend->tv_nsec;
    if (ptsSubtrahend->tv_nsec < ptsReduction->tv_nsec)
    {
        iSecondsDifference--;
        iNanoSecondDifference += NUMBER_OF_NS_IN_PRE_SECOND;
    }
    iNanoSecondDifference -= ptsReduction->tv_nsec;
    ptsOutput->tv_sec = iSecondsDifference;
    ptsOutput->tv_nsec = iNanoSecondDifference;
}
OG_CR_ELECTROMAGNETIC_DOT_TIMER *OgCrCreateElectromagneticDotTimer(int8_t iDotFrequency)
{
    size_t sSizeOfEdtStruct = sizeof(OG_CR_ELECTROMAGNETIC_DOT_TIMER);
    size_t sSizeOfDotTable = sizeof(clock_t) * (iDotFrequency + 1); /*<<这里故意多添加了一个元素 */
    OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt;
    // 检pane spl查参数是否有效
    if (iDotFrequency < 1)
        return NULL;

    // 分配并初始化内存
    pEdt = (OG_CR_ELECTROMAGNETIC_DOT_TIMER *)malloc(sSizeOfEdtStruct);
    if (!pEdt)
        return NULL;
    memset((void *)pEdt, 0, sSizeOfEdtStruct);
    pEdt->piDotTable = (clock_t *)malloc(sSizeOfDotTable);
    if (!pEdt->piDotTable)
    {
        free(pEdt);
        return NULL;
    }
    memset((void *)pEdt->piDotTable, 0, sSizeOfDotTable);
    pEdt->iDotFrequency = iDotFrequency;
    // 填充时间表
    for (uint32_t uIndex = 1; uIndex < iDotFrequency + 1; uIndex++)
    {
        pEdt->piDotTable[uIndex] = NUMBER_OF_NS_IN_PRE_SECOND * uIndex / iDotFrequency;
    }
    return pEdt;
}
void OgCrDestoryElectromagneticDotTimer(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (!pEdt)
        return;
    free((void *)pEdt->piDotTable);
    free((void *)pEdt);
}
int64_t OgCrElectromagneticDotTimerPullTask(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (!pEdt)
        return 0;
    struct timespec tsCurrentTime;
    struct timespec tsTimeDifference;
    int64_t iNsDifference;
    clock_gettime(CLOCK_MONOTONIC, &tsCurrentTime);
    TimespecDifference(&tsCurrentTime, &pEdt->tsLast, &tsTimeDifference);
    iNsDifference = TimespecToInt64(&tsTimeDifference);
    for (size_t sIndex = 0; sIndex < pEdt->iDotFrequency; sIndex++)
    {
        if (iNsDifference >= pEdt->piDotTable[sIndex] && iNsDifference < pEdt->piDotTable[sIndex + 1])
        {
            return sIndex;
        }
    }
    return 0;
}

void OgCrElectromagneticDotTimerSkipATimeStamp(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (!pEdt)
        return;
    struct timespec tsCurrentTime;
    struct timespec tsTimeDifference;
    struct timespec tsTimeToSleep;
    int64_t iTimeDifferenceNanoSecond, iTimeToSleep = 0;
    clock_gettime(CLOCK_MONOTONIC, &tsCurrentTime);
    // 计算应等待的时间
    TimespecDifference(&tsCurrentTime, &pEdt->tsStart, &tsTimeDifference);
    iTimeDifferenceNanoSecond = tsTimeDifference.tv_nsec;
    for (size_t sIndex = 0; sIndex < pEdt->iDotFrequency + 1; sIndex++)
    {
        if (pEdt->piDotTable[sIndex] < tsTimeDifference.tv_nsec &&
            tsTimeDifference.tv_nsec < pEdt->piDotTable[sIndex + 1])
        {
            iTimeToSleep = pEdt->piDotTable[sIndex + 1] - iTimeDifferenceNanoSecond;
            break;
        }
    }
    tsTimeToSleep = Int64ToTimespec(iTimeToSleep);
    // 休眠一段时间
    clock_nanosleep(CLOCK_MONOTONIC, 0, &tsTimeToSleep, NULL);
    clock_gettime(CLOCK_MONOTONIC, &tsCurrentTime);
    // 清空队列
    pEdt->tsLast = tsCurrentTime;
}
void OgCrRefreshElectromagneticDotTimer(OG_CR_ELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (!pEdt)
        return;
    struct timespec tsCurrentTime;
    clock_gettime(CLOCK_MONOTONIC, &tsCurrentTime);
    pEdt->tsLast = tsCurrentTime;
    pEdt->tsStart = tsCurrentTime;
}
#endif
