#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR pCmdLine, int nCmdShow)
{
    WCHAR windowClassName[]{L"OpenSTGLauncherWindowClass"};
    WCHAR windowTitle[]{L"Open Stg Game Launcher"};
    WNDCLASSW windowClass{.lpfnWndProc = DefWindowProc, .hInstance = hInstance, .lpszClassName = windowClassName};
    RegisterClassW(&windowClass);
    HWND hWindow = CreateWindowExW(0, windowClassName, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                   CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);
    if (hWindow == nullptr)
    {
        return EXIT_FAILURE;
    }
    ShowWindow(hWindow, nCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return EXIT_SUCCESS;
}

#ifdef NOT_MSVC
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
    size_t wcharStringSize = strlen(pCmdLine);
    wchar_t* wcharString = (wchar_t*)malloc(wcharStringSize);
    if(wcharString == NULL)
    {
        return EXIT_FAILURE;
    }
    wsprintfW(wcharString,L"%s",pCmdLine);
    wWinMain(hInstance,NULL,wcharString,nCmdShow);
    free((void*)wcharString);
}
#endif