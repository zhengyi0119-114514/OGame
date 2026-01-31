#include "CloseStgCore.h"
#include "CloseStgHistory.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if __has_include("windows.h")
#include <windows.h>
#endif
#if defined __unix__ // POSIX
OG_PRIVATE pthread_key_t s_pkPthreadKey = 0;
#elif OPEN_STG_MACRO_IS_WINDOWS
extern DWORD s_tls;
#endif

BOOL_T ogCrPvInitTSL()
{
#if OPEN_STG_MACRO_IS_WINDOWS
    return OG_TRUE;
#else
    int iStatus = 0;
    iStatus = pthread_key_create(&s_pkPthreadKey, free);
    if (iStatus < 0)
    {
        goto failed;
    }
    return OG_TRUE;
failed:
    return OG_FALSE;
#endif
}
OG_INTERNAL BOOL_T OG_API ogCrPvFreeTSL(void)
{
#if OPEN_STG_MACRO_IS_WINDOWS
    return OG_TRUE;
#else
    int iStatus = 0;
    if ((iStatus = pthread_key_delete(s_pkPthreadKey)) < 0)
    {
        return FALSE;
    }
    return TRUE;
#endif
}
OG_CR_THREAD_LOCAL_STORAGE_STRUCT *OgCrGetTLSStruct(void)
{
#if OPEN_STG_MACRO_IS_WINDOWS
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = (OG_CR_THREAD_LOCAL_STORAGE_STRUCT *)TlsGetValue(s_tls);
    if (ptlss == NULL)
    {
        // FIXME: 有空去查查DllMain()
        fprintf_s(stderr, "%p As TlsGetValue in thread_id %d\n", (void *)ptlss, (int)GetCurrentThreadId());
    }
    return ptlss;
#else
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = (OG_CR_THREAD_LOCAL_STORAGE_STRUCT *)pthread_getspecific(s_pkPthreadKey);
    if (ptlss == NULL)
    {
        size_t sSizeOfTLSSturct = sizeof(OG_CR_THREAD_LOCAL_STORAGE_STRUCT);
        ptlss = (OG_CR_THREAD_LOCAL_STORAGE_STRUCT *)malloc(sSizeOfTLSSturct);
        memset((void *)ptlss, 0, sSizeOfTLSSturct);
        pthread_setspecific(s_pkPthreadKey, (void *)ptlss);
    }
    return ptlss;
#endif
}
char* OG_API OgCrGetCharBuffer(void)
{
    return OgCrGetTLSStruct()->szUniversalBuffer;
}
// NOTE: 实现将放置在DllMain中,Windows实现将不采用PThread
