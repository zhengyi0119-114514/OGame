#if defined _WIN32
#include <OpenStgDefine.h>
#include <windows.h>

DWORD s_tls = 0;

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReson, LPVOID lpvReserved)
{
    switch (fdwReson)
    {
    case DLL_PROCESS_ATTACH: {
        // Init
        s_tls = TlsAlloc();
        break;
    }
    case DLL_PROCESS_DETACH: {
        // Cleanup
        TlsFree(s_tls);
        s_tls = 0;
        break;
    }
    case DLL_THREAD_ATTACH: {
        OgTHREAD_LOCAL_STORAGE_STRUCT *ptlss = (OgTHREAD_LOCAL_STORAGE_STRUCT *)HeapAlloc(
            GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(OgTHREAD_LOCAL_STORAGE_STRUCT));
        TlsSetValue(s_tls, (LPVOID)ptlss);
        break;
    }
    case DLL_THREAD_DETACH: {
        OgTHREAD_LOCAL_STORAGE_STRUCT *ptlss = (OgTHREAD_LOCAL_STORAGE_STRUCT *)TlsGetValue(s_tls);
        HeapFree(GetProcessHeap(), 0, (LPVOID)ptlss);
        break;
    }
    }
    return (TRUE);
}

#endif