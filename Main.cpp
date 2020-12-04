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

    d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);  // Мы не будем использовать освещение
    d3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE); // И буфер глубины тоже

    /*
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &d3dDevice)))
        return E_FAIL;
    */

}

void DrawFrame()
{
    //HRESULT hr = d3dDevice->TestCooperativeLevel();

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

    srand(clock());

    struct Particle
    {
        float x, y, vx, vy;
    };
    std::deque<Particle> particles;
    Particle tmp;
    int particleCount = 10;

    for (int i = 0; i < particleCount; ++i)
    {
        tmp.x = rand() % g_iWindowWidth;
        tmp.y = rand() % g_iWindowHeight;

        particles.push_back(tmp);
    }

    LPDIRECT3DVERTEXBUFFER9 pVertexObject = NULL;
    LPDIRECT3DVERTEXDECLARATION9 vertexDecl = NULL;

    struct VertexData
    {
        float x, y, z, u, v;
    };

    size_t count = particles.size();
    VertexData* vertexData = new VertexData[count];

    for (size_t i = 0; i < count; ++i)
    {
        vertexData[i].x = particles[i].x;
        vertexData[i].y = particles[i].y;
        vertexData[i].z = 0.f;
        vertexData[i].u = 0;
        vertexData[i].v = 0;
    }

    void* pVertexBuffer = NULL;

    //Создание вершинного буфера
    if(FAILED(d3dDevice->CreateVertexBuffer(
        count * sizeof(VertexData),
        D3DUSAGE_WRITEONLY,
        D3DFVF_XYZ,
        D3DPOOL_DEFAULT,
        &pVertexObject,
        NULL)))
    {
        Shutdown();
        MessageBox(NULL, L"Can`t create vertex buffer", L"Error", MB_OK | MB_ICONERROR);
        return;
    };

    // Блокировка буфера, чтобы записать туда данные о вершинах
    pVertexObject->Lock(0, count * sizeof(VertexData), &pVertexBuffer, 0);

    memcpy(pVertexBuffer, vertexData, count * sizeof(VertexData));

    pVertexObject->Unlock();

    delete[] vertexData;
    vertexData = nullptr;

    D3DVERTEXELEMENT9 decl[] =
    {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        D3DDECL_END()
    };

    // Создаем объект с описанием вершин
    if (FAILED(d3dDevice->CreateVertexDeclaration(decl, &vertexDecl)))
    {
            Shutdown();
            MessageBox(NULL, L"Can`t create vertex declaration", L"Error", MB_OK | MB_ICONERROR);
            return;
    };



    d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

    // Устанавливаем источник вершин
    d3dDevice->SetStreamSource(0, pVertexObject, 0, sizeof(VertexData));
    // Указываем, что хранится в буфере
    d3dDevice->SetVertexDeclaration(vertexDecl);

    d3dDevice->BeginScene();

    if (FAILED(d3dDevice->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_POINTLIST,
        0,
        particles.size())))
    {
        Shutdown();
        MessageBox(NULL, L"Can`t create vertex declaration", L"Error", MB_OK | MB_ICONERROR);
        return;
    };

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