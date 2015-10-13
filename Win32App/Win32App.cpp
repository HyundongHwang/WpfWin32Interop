#include "stdafx.h"
#include "Win32App.h"
#include "MainWnd.h"

[System::STAThreadAttribute]
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    g_hInst = hInstance;
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    int cx = ::GetSystemMetrics(SM_CXSCREEN);
    int cy = ::GetSystemMetrics(SM_CYSCREEN);

    MainWnd mainWnd;
    mainWnd.Create(NULL, CRect(300, 300, cx - 300, cy - 300), L"MainWnd",
        WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE,
        0);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}