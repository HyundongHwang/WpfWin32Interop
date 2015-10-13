#pragma once
class MainWnd
    : public CWindowImpl < MainWnd >
{
public:
    MainWnd();
    virtual ~MainWnd();

    DECLARE_WND_CLASS(L"MainWnd")

    BEGIN_MSG_MAP(MainWnd)
        MESSAGE_HANDLER(WM_CREATE, _On_WM_CREATE)
    END_MSG_MAP()
    
    void OnFromManaged(wchar_t* pwMsg);



private:
    LRESULT _On_WM_CREATE(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);



    HWND m_hWndWPF;
    gcroot<HhdCalcControl^> m_HhdCalcControl;
};

