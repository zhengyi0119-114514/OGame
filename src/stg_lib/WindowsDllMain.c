#if OPEN_STG_MACRO_IS_WINDOWS
#include <OpenStgDefine.h>
#include <windows.h>


OG_INTERNAL DWORD s_tls = 0;

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
        //  break;
        /*主线程在调用DllMain(DLL_PROCESS_ATTACH)后不会调用DllMain(DLL_THREAD_ATTACH)*/
    }
    case DLL_THREAD_ATTACH: {
        OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = (OG_CR_THREAD_LOCAL_STORAGE_STRUCT *)HeapAlloc(
            GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(OG_CR_THREAD_LOCAL_STORAGE_STRUCT));
        if (ptlss != NULL)
        {
            TlsSetValue(s_tls, (LPVOID)ptlss);
        }
        break;
    }
    case DLL_PROCESS_DETACH: {
        // Cleanup
        TlsFree(s_tls);
        break;
    }
    case DLL_THREAD_DETACH: {
        OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = (OG_CR_THREAD_LOCAL_STORAGE_STRUCT *)TlsGetValue(s_tls);
        if (ptlss != NULL)
        {
            HeapFree(GetProcessHeap(), 0, (LPVOID)ptlss);
        }
        break;
    }
    }
    return (TRUE);
}

#endif
