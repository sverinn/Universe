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
#include <deque>
#include "Console.h"
#include <string>
#include <thread>
#include <mutex>


//Глобальные переменные
HINSTANCE g_hInstance = NULL;      //Дескриптор приложения
HWND g_hWnd = NULL;            //Дескриптор окна
int g_iWindowWidth = 1024;        //Ширина окна
int g_iWindowHeight = 768;        //Высота окна
bool g_bApplicationState = true;    //Состояние приложения (true - работает/false - не работает)
IDirect3D9* g_pD3D = NULL;      //Интерфейс для создания устройства рендеринга
IDirect3DDevice9* d3dDevice = NULL;  //Интерфейс устройства рендеринга
int timescale = 1000000;
bool ShowConsole = false;
int DeviceCoreCount = std::thread::hardware_concurrency();
bool keys[256];
int ParallelMode = 2;
double Scale = 1e-7;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow); //Точка старта приложения
static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);//Обработчик сообщений
bool InitDirect3D(D3DFORMAT ColorFormat, D3DFORMAT DepthFormat);    //Инициализация Direct3D
void DrawFrame(std::vector<PhysicalObject*> ObjectReg);
void Shutdown();
void DebugEcho(std::vector<PhysicalObject*> ObjectReg);
double eps(double value);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int(nShowCmd))
{
    
        if (ShowConsole)
            CallConsole();

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
    
    std::vector<PhysicalObject*> ObjectReg;
    int particleCount = 200;

    srand(clock());


    /*
    ObjectReg.push_back(new PhysicalObject(10.0, 384.0, SolarMass * Scale, eps(SolarRadius * Scale), 0, 0));
    ObjectReg[0]->ShowInfo();
    ObjectReg.push_back(new PhysicalObject(10.0 + (SolarRadius + EarthSunDistance + EarthRadius) * Scale, 384.0, EarthMass * Scale, eps(EarthRadius * Scale), 0, eps(EarthSunVelocity * Scale)));
    ObjectReg[1]->ShowInfo();
    */

    
    for (int i = 0; i < particleCount; ++i)
    {
        
        double randX = 1 + rand() % g_iWindowWidth;
        double randY = 1 + rand() % g_iWindowHeight;
        double randMass = 10 + rand() % 100 * 100;
        //double randMass = 10000;
        if (i > 0)
        while (fabs(ObjectReg[i - 1]->GetX() - randX) < 1 && fabs(ObjectReg[i - 1]->GetY() - randY) < 1)
        {
            randX = rand() % g_iWindowWidth;
            randY = rand() % g_iWindowHeight;
            randMass = 10 + rand() % 100 * 100;
            //randMass = 10000;
        }
        if (randX > g_iWindowWidth / 2)
            ObjectReg.push_back(new PhysicalObject(randX, randY, randMass, sqrtf(randMass) / 20, 0, 0));
        else
            ObjectReg.push_back(new PhysicalObject(randX, randY, randMass, sqrtf(randMass) / 20, 0, 0));
    }
    
    while (g_bApplicationState)
    {
        
        //if (rand()%173 == 0)
        //if (std::to_string(ObjectReg[1]->GetX()) == "-nan(ind)")
        //{
        //    return -1;
        //}

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /*
            bool fHandled = false;
            //if (msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST)
               fHandled = MyHandleMouseEvent(&msg);
            if (msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST)
            {
            }
            else if (WM_QUIT == msg.message)
                break;
            if (!fHandled)
            */
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else if (ObjectReg.size() > 0)
        {
            if (keys[37])
                timescale /= 2;
            if (keys[39])
                timescale *= 2;
            if (ParallelMode == 1)
            {
                //std::thread PhysicsThread(UpdatePhysics, std::ref(ObjectReg), timescale);
                std::thread GraphicsThread(DrawFrame, ObjectReg);
                std::thread ConsoleThread(DebugEcho, ObjectReg);
                GraphicsThread.join();
                //PhysicsThread.join();
                ConsoleThread.join();
            }
            else if (ShowConsole)
            {
                std::thread ConsoleThread(DebugEcho, ObjectReg);
                UpdatePhysics(ObjectReg, timescale);
                DrawFrame(ObjectReg);
                ConsoleThread.join();
            }
            else
            {
                UpdatePhysics(ObjectReg, timescale);
                DrawFrame(ObjectReg);
            }
        }
        else
        {
            Shutdown();
            MessageBox(NULL, L"Object array is empty!", L"Error", MB_OK | MB_ICONERROR);
            return 0;
        };

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

    memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

    if (SUCCEEDED(g_pD3D->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        g_hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3dDevice)))
        return true;

    d3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(255, 255, 255, 255));  //Ambient light level = 1
    d3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE); // И буфер глубины тоже
    d3dDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);

    /*
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &d3dDevice)))
        return E_FAIL;
    */

}

std::mutex GraphicsThreadMutex;

void DrawFrame(std::vector<PhysicalObject*> ObjectReg)
{
    //HRESULT hr = d3dDevice->TestCooperativeLevel();
    GraphicsThreadMutex.lock();
    if (d3dDevice->TestCooperativeLevel() == D3DERR_DEVICELOST)
        return;

    // Инициализация матриц
    D3DXMATRIX matrixView;
    D3DXMATRIX matrixProjection;

    D3DXVECTOR3 Vector1(0, 0, 0);
    D3DXVECTOR3 Vector2(0, 0, 1);
    D3DXVECTOR3 Vector3(0, 1, 0);


    // Матрица вида
    D3DXMatrixLookAtLH(
        &matrixView,
        &Vector1,
        &Vector2,
        &Vector3);

    // Матрица проекции
    D3DXMatrixOrthoOffCenterLH(&matrixProjection, 0, g_iWindowWidth, g_iWindowHeight, 0, 0, 255);

    // Установка матриц в качестве текущих
    d3dDevice->SetTransform(D3DTS_VIEW, &matrixView);
    d3dDevice->SetTransform(D3DTS_PROJECTION, &matrixProjection);



    LPDIRECT3DVERTEXBUFFER9 pVertexObject = NULL;
    LPDIRECT3DVERTEXDECLARATION9 vertexDecl = NULL;
    void* pVertexBuffer = nullptr;
    
    size_t Stride = RenderPointlist(d3dDevice, pVertexObject, vertexDecl, pVertexBuffer, ObjectReg);

    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(150, 150, 150), 1.0f, 0);

    // Устанавливаем источник вершин
    d3dDevice->SetStreamSource(0, pVertexObject, 0, Stride);
    // Указываем, что хранится в буфере
    d3dDevice->SetVertexDeclaration(vertexDecl);

    d3dDevice->BeginScene();

    if (FAILED(d3dDevice->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_POINTLIST,
        0,
        ObjectReg.size())))
    {
        Shutdown();
        MessageBox(NULL, L"Can`t create vertex declaration", L"Error", MB_OK | MB_ICONERROR);
        return;
    };

    d3dDevice->EndScene();
    d3dDevice->Present(NULL, NULL, NULL, NULL);
    GraphicsThreadMutex.unlock();
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

void DebugEcho(std::vector<PhysicalObject*> ObjectReg)
{
    for (int i = 0; i < ObjectReg.size(); i++)
    {
        ObjectReg[i]->ShowInfo();
    }
}


double eps(double value)
{
    if (abs(value) < EPS)
        return 0.0;
    else
        return value;
};