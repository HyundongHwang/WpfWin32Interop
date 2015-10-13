#include "stdafx.h"
#include "MainWnd.h"



using namespace System::Windows::Interop;



static void _OnFromManaged(int thisObj, String^ msg)
{
    MainWnd* pThis = (MainWnd*)(thisObj);
    std::wstring wMsg = marshal_as<std::wstring>(msg);
    pThis->OnFromManaged((wchar_t*)wMsg.c_str());
}

MainWnd::MainWnd()
{
}

MainWnd::~MainWnd()
{
}

void MainWnd::OnFromManaged(wchar_t* pwMsg)
{
    {
        CStringW strMsg = L"";
        strMsg.Format(L"MainWnd::OnFromManaged pwMsg : %s", pwMsg);
        ::MessageBoxW(NULL, strMsg, NULL, MB_OK);//hhddebug
    }
}

LRESULT MainWnd::_On_WM_CREATE(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    HwndSourceParameters params("MainWnd");
    params.PositionX = 0;
    params.PositionY = 0;
    params.Height = 300;
    params.Width = 300;
    params.ParentWindow = (IntPtr)this->m_hWnd;
    params.WindowStyle = WS_VISIBLE | WS_CHILD;
    HwndSource^ hwndSrcObj = gcnew HwndSource(params);

    this->m_HhdCalcControl = gcnew HhdCalcControl();
    this->m_HhdCalcControl->Init((int)this);
    this->m_HhdCalcControl->CallNative = gcnew HhdCallNativeDele(_OnFromManaged);
    hwndSrcObj->RootVisual = this->m_HhdCalcControl;
    HWND hwndHhdCalcControl = (HWND)hwndSrcObj->Handle.ToPointer();

    {
        CStringW strMsg = L"";
        strMsg.Format(L"MainWnd::_On_WM_CREATE hwndHhdCalcControl : %d\n", hwndHhdCalcControl);
        ::MessageBoxW(NULL, strMsg, NULL, MB_OK);//hhddebug
    }

    return 0;
}