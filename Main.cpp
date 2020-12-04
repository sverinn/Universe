#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")


#include "Physics.h"
#include "Renderer.h"
#include "ObjectHandler.h"
#include "Constants.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>



//Глобальные переменные
HINSTANCE g_hInstance = NULL;      //Дескриптор приложения
HWND g_hWnd = NULL;            //Дескриптор окна
int g_iWindowWidth = 800;        //Ширина окна
int g_iWindowHeight = 600;        //Высота окна
bool g_bApplicationState = true;    //Состояние приложения (true - работает/false - не работает)
IDirect3D9* g_pD3D = NULL;      //Интерфейс для создания устройства рендеринга
IDirect3DDevice9* d3dDevice = NULL;  //Интерфейс устройства рендеринга



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow); //Точка старта приложения
static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);//Обработчик сообщений
bool InitDirect3D(D3DFORMAT ColorFormat, D3DFORMAT DepthFormat);    //Инициализация Direct3D
void DrawFrame();
void Shutdown();



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
    g_hInstance = GetModuleHandle(NULL);

    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;              //Функция обработки сообщений
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = g_hInstance;            //Дескриптор приложения
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = L"UniverseD3Dx";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


    if (!RegisterClassEx(&wc))
    {
        Shutdown();
        MessageBox(NULL, L"Can`t register window class", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    g_hWnd = CreateWindowExW(
        WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
        L"UniverseD3Dx",
        L"UniverseD3D - Window",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        0,
        0,
        g_iWindowWidth,
        g_iWindowHeight,
        NULL,
        NULL,
        g_hInstance,
        NULL);

    if (g_hWnd == NULL)
    {
        Shutdown();
        MessageBox(NULL, L"Can`t create window", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    if (!(InitDirect3D(D3DFMT_R5G6B5, D3DFMT_D16)))
    {
        Shutdown();
        MessageBox(NULL, L"Can`t create direct3d", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(g_hWnd, SW_SHOW);
    UpdateWindow(g_hWnd);
    SetFocus(g_hWnd);
    SetForegroundWindow(g_hWnd);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (g_bApplicationState)
    {
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
            DrawFrame();
    }

    Shutdown();

    return 0;
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
    case WM_DESTROY:
    {
        g_bApplicationState = false;
        return 0;
    }
    }

    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

bool InitDirect3D(D3DFORMAT ColorFormat, D3DFORMAT DepthFormat)
{

    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    LPDIRECT3DDEVICE9 pDevice = NULL;

    //HRESULT hr = NULL;

    D3DDISPLAYMODE DisplayMode;
    g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode);



    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.hDeviceWindow = g_hWnd;
    d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
    d3dpp.BackBufferWidth = g_iWindowWidth;
    d3dpp.BackBufferHeight = g_iWindowHeight;
    d3dpp.BackBufferCount = 1;
    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.AutoDepthStencilFormat = DepthFormat;
    d3dpp.BackBufferFormat = DisplayMode.Format;

    if (SUCCEEDED(g_pD3D->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        g_hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3dDevice)))
        return true;

    if (SUCCEEDED(g_pD3D->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        g_hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3dDevice)))
        return true;


    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &d3dDevice)))
        return E_FAIL;

}

void DrawFrame()
{
    //HRESULT hr = d3dDevice->TestCooperativeLevel();

    if (d3dDevice->TestCooperativeLevel() == D3DERR_DEVICELOST)
        return;

    d3dDevice->Clear(
        0L,
        NULL,
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        D3DCOLOR_XRGB(0, 0, 0),
        1.0f,
        0L);

    d3dDevice->BeginScene();
    d3dDevice->EndScene();
    d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Shutdown()
{
    if (d3dDevice != NULL)
    {
        d3dDevice->Release();
        d3dDevice = NULL;
    }

    if (g_pD3D != NULL)
    {
        g_pD3D->Release();
        g_pD3D = NULL;
    }

    if (!DestroyWindow(g_hWnd))
        g_hWnd = NULL;

    if (!UnregisterClass(L"UniverseD3D", g_hInstance))
        g_hInstance = NULL;
}


//Код для рендера через SFML
/*
int main()
{
    
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Universe Simulator");
    std::vector<PhysicalObject*> ObjectReg;

    while (window.isOpen())
    {
        UpdatePhysics(ObjectReg);
        RenderScene(window, ObjectReg);
        //for (auto iObject : ObjectReg)
        //    iObject->ShowInfo();
    }
    
    return 0;
}
*/