#if defined _WIN32
#include <OpenStgDefine.h>
#include <stdio.h>
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
        // fprintf_s(stderr, "WHAT DO TlsAlloc RETURN?,%d\n", (int)s_tls);
        // break;
    }
    case DLL_THREAD_ATTACH: {
        OG_THREAD_LOCAL_STORAGE_STRUCT *ptlss = (OG_THREAD_LOCAL_STORAGE_STRUCT *)HeapAlloc(
            GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(OG_THREAD_LOCAL_STORAGE_STRUCT));
        if (ptlss != NULL)
        {
            // fprintf_s(stderr, "%p As OG_THREAD_LOCAL_STORAGE_STRUCT in %d\n", (void *)ptlss, (int)GetCurrentThreadId());
            TlsSetValue(s_tls, (LPVOID)ptlss);
            // fprintf_s(stderr, "%p is returned\n", TlsGetValue(s_tls));
        }
        break;
    }
    case DLL_THREAD_DETACH: {
        OG_THREAD_LOCAL_STORAGE_STRUCT *ptlss = (OG_THREAD_LOCAL_STORAGE_STRUCT *)TlsGetValue(s_tls);
        fprintf_s(stderr, "%p is returned\n", (void *)ptlss);
        if (ptlss != NULL)
        {
            HeapFree(GetProcessHeap(), 0, (LPVOID)ptlss);
        }
        break;
    }
    case DLL_PROCESS_DETACH: {
        // Cleanup
        TlsFree(s_tls);
        break;
    }
    }
    return (TRUE);
}

#endif
