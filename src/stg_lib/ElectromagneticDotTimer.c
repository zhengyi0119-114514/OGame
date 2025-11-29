#include "CloseStg.h"

#if defined WIN32 || WINDOWS32

OgELECTROMAGNETIC_DOT_TIMER *OgElectromagneticDotTimerCreate(int8_t iFrequency)
{
    if (iFrequency < 1)
        return NULL;
    // 分配并初始化内存
    size_t edtSize = sizeof(OgELECTROMAGNETIC_DOT_TIMER);
    size_t edtTimeTableCount = iFrequency + 1;
    OgELECTROMAGNETIC_DOT_TIMER *pedt = (OgELECTROMAGNETIC_DOT_TIMER *)malloc(edtSize);
    if (!pedt)
        return NULL;
    ZeroMemory((void *)pedt, edtSize);
    pedt->pliDotTable = (LARGE_INTEGER *)malloc(edtTimeTableCount * sizeof(LARGE_INTEGER));
    if (!pedt)
    {
        free((void *)pedt);
        return NULL;
    }
    ZeroMemory((void *)pedt->pliDotTable, edtTimeTableCount * sizeof(LARGE_INTEGER));
    QueryPerformanceFrequency(&(pedt->liFrequency));
    // 填充时间表
    for (size_t sIndex = 1; sIndex <= iFrequency; sIndex++)
    {
        pedt->pliDotTable[sIndex].QuadPart = pedt->liFrequency.QuadPart * iFrequency / sIndex;
    }
    return pedt;
}
void OgElectromagneticDotTimerDestory(OgELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (pEdt)
    {
        if (pEdt->pliDotTable)
            free((void *)pEdt->pliDotTable);
        free((void *)pEdt);
    }
}
int64_t OgElectromagneticDotTimerPullTask(OgELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    int64_t iResult = 0;
    LARGE_INTEGER liCurrentTime;

    QueryPerformanceCounter(&liCurrentTime);
    iResult += liCurrentTime.QuadPart / pEdt->liFrequency.QuadPart;
    liCurrentTime.QuadPart %= pEdt->liFrequency.QuadPart;
    for (size_t sIndex = 0; sIndex < pEdt->iFrequency + 1; sIndex++)
    {
        if (pEdt->pliDotTable[sIndex].QuadPart <= liCurrentTime.QuadPart &&
            liCurrentTime.QuadPart < pEdt->pliDotTable[sIndex + 1].QuadPart)
        {
            iResult += sIndex;
            break;
        }
    }
    return iResult;
}
void OgElectromagneticDotTimerRefresh(OgELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    LARGE_INTEGER liCurrentTime;
    QueryPerformanceCounter(&liCurrentTime);
    pEdt->liLast = liCurrentTime;
    pEdt->liStart = liCurrentTime;
}
void OgElectromagneticDotTimerSkipATimeStamp(OgELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    LARGE_INTEGER liTimeDifference;
    LARGE_INTEGER liCurrentTime;
    LARGE_INTEGER liTimeSleepTarget;
    LARGE_INTEGER liTimeToSleep;
    DWORD dwMsToSleep = 0;
    QueryPerformanceCounter(&liCurrentTime);
    liTimeDifference.QuadPart = liCurrentTime.QuadPart - pEdt->liFrequency.QuadPart;
    liTimeDifference.QuadPart %= pEdt->liFrequency.QuadPart;
    for (size_t sIndex = 0; sIndex < pEdt->iFrequency + 1; sIndex++)
    {
        if (pEdt->pliDotTable[sIndex].QuadPart < liTimeDifference.QuadPart &&
            liTimeDifference.QuadPart < pEdt->pliDotTable[sIndex + 1].QuadPart)
        {
            liTimeToSleep.QuadPart = pEdt->pliDotTable[sIndex + 1].QuadPart - liTimeDifference.QuadPart;
            liTimeSleepTarget.QuadPart = liCurrentTime.QuadPart + liTimeToSleep.QuadPart;
            dwMsToSleep = (liTimeToSleep.QuadPart * 1000 / pEdt->liFrequency.QuadPart) % 10;
            dwMsToSleep = dwMsToSleep / 15 * 15;
            break;
        }
    }
    Sleep(dwMsToSleep);
    while (TRUE)
    {
        QueryPerformanceCounter(&liCurrentTime);
        if (liCurrentTime.QuadPart >= liTimeSleepTarget.QuadPart)
            break;
    }
    pEdt->liLast = liCurrentTime;
}
#elif defined POSIX
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMBER_OF_NS_IN_PRE_SECOND ((int64_t)(1000000000))
OPEN_STG_PRIVATE OPEN_STG_CDECL inline void TimespecDifference(struct timespec *ptsSubtrahend,
                                                               struct timespec *ptsReduction,
                                                               struct timespec *ptsOutput);
OPEN_STG_PRIVATE OPEN_STG_CDECL inline int64_t TimespecToInt64(struct timespec *pts);
OPEN_STG_PRIVATE OPEN_STG_CDECL inline struct timespec Int64ToTimespec(int64_t i);

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
OgELECTROMAGNETIC_DOT_TIMER *OgElectromagneticDotTimerCreate(int8_t iFrequency)
{
    size_t sSizeOfEdtStruct = sizeof(OgELECTROMAGNETIC_DOT_TIMER);
    size_t sSizeOfDotTable = sizeof(clock_t) * (iFrequency + 1); /*<<这里故意多添加了一个元素 */
    OgELECTROMAGNETIC_DOT_TIMER *pEdt;
    // 检查参数是否有效
    if (iFrequency < 1)
        return NULL;

    // 分配并初始化内存
    pEdt = (OgELECTROMAGNETIC_DOT_TIMER *)malloc(sSizeOfEdtStruct);
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
    pEdt->iFrequency = iFrequency;
    // 填充时间表
    for (size_t sIndex = 1; sIndex < iFrequency + 1; sIndex++)
    {
        pEdt->piDotTable[sIndex] = NUMBER_OF_NS_IN_PRE_SECOND * sIndex / iFrequency;
    }
    return pEdt;
}
void OgElectromagneticDotTimerDestory(OgELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (!pEdt)
        return;
    free((void *)pEdt->piDotTable);
    free((void *)pEdt);
}
int64_t OgElectromagneticDotTimerPullTask(OgELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (!pEdt)
        return 0;
    struct timespec tsCurrentTime;
    struct timespec tsTimeDifference;
    int64_t iNsDifference;
    clock_gettime(CLOCK_MONOTONIC, &tsCurrentTime);
    TimespecDifference(&tsCurrentTime, &pEdt->tsLast, &tsTimeDifference);
    iNsDifference = TimespecToInt64(&tsTimeDifference);
    for (size_t sIndex = 0; sIndex < pEdt->iFrequency; sIndex++)
    {
        if (iNsDifference >= pEdt->piDotTable[sIndex] && iNsDifference < pEdt->piDotTable[sIndex + 1])
        {
            return sIndex;
        }
    }
    return 0;
}

void OgElectromagneticDotTimerSkipATimeStamp(OgELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (!pEdt)
        return;
    struct timespec tsCurrentTime;
    struct timespec tsTimeDifference;
    struct timespec tsTimeToSleep;
    int64_t iTimeDifferenceNanoSecond, iTimeToSleep;
    clock_gettime(CLOCK_MONOTONIC, &tsCurrentTime);
    // 计算应等待的时间
    TimespecDifference(&tsCurrentTime, &pEdt->tsStart, &tsTimeDifference);
    iTimeDifferenceNanoSecond = tsTimeDifference.tv_nsec;
    for (size_t sIndex = 0; sIndex < pEdt->iFrequency + 1; sIndex++)
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
void OgElectromagneticDotTimerRefresh(OgELECTROMAGNETIC_DOT_TIMER *pEdt)
{
    if (!pEdt)
        return;
    struct timespec tsCurrentTime;
    clock_gettime(CLOCK_MONOTONIC, &tsCurrentTime);
    pEdt->tsLast = tsCurrentTime;
    pEdt->tsStart = tsCurrentTime;
}
#endif