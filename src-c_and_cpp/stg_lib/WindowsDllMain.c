#if OPEN_STG_MACRO_IS_WINDOWS
#include <OpenStg/OpenStgDefine.h>
#include <windows.h>

OG_INTERNAL DWORD s_tls = 0;
OG_ALWAYS_INLINE inline void OG_API AllocTLSStructAndSet()
{
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = (OG_CR_THREAD_LOCAL_STORAGE_STRUCT *)HeapAlloc(
        GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(OG_CR_THREAD_LOCAL_STORAGE_STRUCT));
    if (ptlss != NULL)
    {
        TlsSetValue(s_tls, (LPVOID)ptlss);
    }
}
OG_ALWAYS_INLINE inline void FreeTLSStruct()
{
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = (OG_CR_THREAD_LOCAL_STORAGE_STRUCT *)TlsGetValue(s_tls);
    if (ptlss != NULL)
    {
        HeapFree(GetProcessHeap(), 0, (LPVOID)ptlss);
    }
    TlsSetValue(s_tls,NULL);
}
BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH: {
        // Init
        s_tls = TlsAlloc();
        if (s_tls == TLS_OUT_OF_INDEXES)
        {
            return FALSE; // FIXME: 修你大爷修
        }
        AllocTLSStructAndSet();
    }
    break;
    case DLL_THREAD_ATTACH: {
        AllocTLSStructAndSet();
    }
    break;
    case DLL_PROCESS_DETACH: {
        // Cleanup
        FreeTLSStruct();
        TlsFree(s_tls);
    }
    break;
    case DLL_THREAD_DETACH: {
        FreeTLSStruct();
    }
    break;
    }
    return (TRUE);
}
#endif
