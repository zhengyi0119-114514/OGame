#include "CloseStg.h"
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
#elif defined _WIN32
extern DWORD s_tls;
#endif

OG_BOOL_T inilTSL(uint64_t ufInitFlag)
{
#if defined _WIN32
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
OG_INTERNAL OG_BOOL_T OG_CDECL quitTSL(void)
{
#if defined _WIN32
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
OG_THREAD_LOCAL_STORAGE_STRUCT *OgGetTLSStruct(void)
{
#if defined _WIN32
    OG_THREAD_LOCAL_STORAGE_STRUCT *ptlss = (OG_THREAD_LOCAL_STORAGE_STRUCT *)TlsGetValue(s_tls);
    if (ptlss == NULL)
    {
        // FIXME: 有空去查查DllMain()
        fprintf_s(stderr, "%p As TlsGetValue in thread_id %d\n", (void *)ptlss, (int)GetCurrentThreadId());
    }
    return ptlss;
#else
    OG_THREAD_LOCAL_STORAGE_STRUCT *ptlss = (OG_THREAD_LOCAL_STORAGE_STRUCT *)pthread_getspecific(s_pkPthreadKey);
    if (ptlss == NULL)
    {
        int iStatus = 0;
        size_t sSizeOfTLSSturct = sizeof(OG_THREAD_LOCAL_STORAGE_STRUCT);
        ptlss = (OG_THREAD_LOCAL_STORAGE_STRUCT *)malloc(sSizeOfTLSSturct);
        memset((void *)ptlss, 0, sSizeOfTLSSturct);
        pthread_setspecific(s_pkPthreadKey, (void *)ptlss);
    }
    return ptlss;
#endif
}
// NOTE: 实现将放置在DllMain中,Windows实现将不采用PThread
