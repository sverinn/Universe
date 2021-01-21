#include "Window.h"
#include "windowsx.h"

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass()
    :
    hInstance(GetModuleHandle(NULL))
{
    WNDCLASSEXW wc;
    wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = HandleMsgSetup;              //������� ��������� ���������
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = Instance();            //���������� ����������
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = ClassName();
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassExW(&wc))
    {
        MessageBoxW(NULL, L"Can`t register window class", L"Error", MB_OK | MB_ICONERROR);
    }
}

const wchar_t* Window::WindowClass::ClassName()
{
    return wndClassNameW;
}

HINSTANCE Window::WindowClass::Instance()
{
    return wndClass.hInstance;
}

Window::WindowClass::~WindowClass()
{
    if (!UnregisterClassW(wndClassNameW, hInstance))
    {
        hInstance = NULL;
        OutputDebugStringW(L"Unregistered Window class\n");
    }
}

Window::Window(int Width, int Height, LPCWSTR Name)
{
    g_bApplicationState = true;
    g_iWindowWidth = Width;
    g_iWindowHeight = Height;

    RECT wr;
    wr.left = 100;
    wr.right = Width + wr.left;
    wr.top = 100;
    wr.bottom = Height + wr.top;

    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

    g_hWnd = CreateWindowExW(
        WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
        WindowClass::ClassName(),
        Name,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        wr.right - wr.left,
        wr.bottom - wr.top,
        NULL,
        NULL,
        WindowClass::Instance(),
        this);

    if (g_hWnd == NULL)
    {
        this->~Window();
        MessageBoxW(NULL, L"Can`t create window", L"Error", MB_OK | MB_ICONERROR);
    }
    ZeroMemory(&msg, sizeof(msg));

    ShowWindow(g_hWnd, SW_SHOW);
    //UpdateWindow(g_hWnd);
    //SetFocus(g_hWnd);
    //SetForegroundWindow(g_hWnd);
    pGfx = std::make_unique<Graphics>(g_hWnd);
}

int Window::ProcessMessages()
{
    MSG msg;
    // while queue has messages, remove and dispatch them (but do not block on empty queue)
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        // check for quit because peekmessage does not signal this via return val
        if (msg.message == WM_QUIT)
        {
            // return optional wrapping int (arg to PostQuitMessage is in wparam) signals quit
            return (int)msg.wParam;
        }

        // TranslateMessage will post auxilliary WM_CHAR messages from key msgs
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

int Window::Width()
{
    return g_iWindowWidth;
}

int Window::Height()
{
    return g_iWindowHeight;
}

LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    if (iMsg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreateStruct = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreateStruct->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
        return pWnd->HandleMsg(hWnd, iMsg, wParam, lParam);
    }
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, iMsg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        g_bApplicationState = false;
        break;
    case WM_KEYDOWN:
        if (wParam == 'F')
        {
        }
        break;
    case WM_KEYUP:
        SetWindowText(hWnd, L"Text");
        break;
            
    case WM_LBUTTONDOWN:
         GET_X_LPARAM(lParam);
         GET_Y_LPARAM(lParam);
         break;
    }

    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

Window::~Window()
{
    if (!DestroyWindow(g_hWnd))
    {
        g_hWnd = NULL;
        OutputDebugStringW(L"Destroyed Window handle\n");
    }
}

bool Window::ApplicationState()
{
    return g_bApplicationState;
}

HWND Window::hWnd()
{
    return g_hWnd;
}

Graphics& Window::Gfx()
{
    return *pGfx;
}