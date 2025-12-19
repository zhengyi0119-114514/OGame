#include "CloseStg.h"
#include "CloseStgHistory.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#if !defined _WIN32 // POSIX
OG_PRIVATE pthread_key_t s_pkPthreadKey = 0;

OG_BOOL inilTSL(uint64_t ufInitFlag)
{
    int iStatus = 0;
    iStatus = pthread_key_create(&s_pkPthreadKey, free);
    if (iStatus < 0)
    {
        goto failed;
    }
    return OG_TRUE;
failed:
    return OG_FALSE;
}
OG_INTERNAL OG_CDECL OG_BOOL quitTSL(void)
{
    int iStatus =0;
    if((iStatus = pthread_key_delete(s_pkPthreadKey))<0)
    {
        return FALSE;
    }
    return TRUE;
}
//分配内存
OgTHREAD_LOCAL_STORAGE_STRUCT *OgThreadInitTSL(void)
{
    int iStatus = 0;
    size_t sSizeOfTLSSturct = sizeof(OgTHREAD_LOCAL_STORAGE_STRUCT);
    OgTHREAD_LOCAL_STORAGE_STRUCT *ptlss = (OgTHREAD_LOCAL_STORAGE_STRUCT *)malloc(sSizeOfTLSSturct);
    memset((void *)ptlss, 0, sSizeOfTLSSturct);
    pthread_setspecific(s_pkPthreadKey, (void *)ptlss);
    return ptlss;
}
OgTHREAD_LOCAL_STORAGE_STRUCT *OgGetTLSStruct(void)
{
    OgTHREAD_LOCAL_STORAGE_STRUCT *ptlss = (OgTHREAD_LOCAL_STORAGE_STRUCT *)pthread_getspecific(s_pkPthreadKey);
    if (!ptlss)
        return OgThreadInitTSL();
    return ptlss;
}
#else
extern DWORD s_tls;
// NOTE: 实现将放置在DllMain中,Windows实现将不采用PThread

OgBoolean OgInitTSL(uint64_t ufInitFlag)
{
    return OG_TRUE;
}
OgTHREAD_LOCAL_STORAGE_STRUCT *OgGetTLSStruct()
{
    return (OgTHREAD_LOCAL_STORAGE_STRUCT*)TlsGetValue(s_tls);
}
OgBoolean quitTSL(void)
{
    return OG_TRUE;
}
#endif
