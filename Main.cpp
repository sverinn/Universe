#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")


#include "Physics.h"
#include "Renderer.h"
#include "ObjectHandler.h"
#include "Constants.h"
#include <windows.h>
#include <d3d12.h>
#include "d3dx12.h"
#include "Console.h"
#include <string>
#include <thread>
#include <mutex>

//#define CType float


//Глобальные переменные
HINSTANCE g_hInstance = NULL;      //Дескриптор приложения
HWND g_hWnd = NULL;            //Дескриптор окна
int g_iWindowWidth = 1024;
int g_iWindowHeight = 768;
bool g_bApplicationState = true;

int timescale = 1000;
bool ShowConsole = false;
const int DeviceCoreCount = std::thread::hardware_concurrency();
bool keys[256];
int ParallelMode = 2;
double Scale = 1e-7;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow); //Точка старта приложения
static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);//Обработчик сообщений
bool InitDirect3D();    //Инициализация Direct3D
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

        if (!(InitDirect3D()))
        {
            //Shutdown();
            MessageBox(NULL, L"Can`t create direct3d", L"Error", MB_OK | MB_ICONERROR);
            //return 0;
        }

        ShowWindow(g_hWnd, SW_SHOW);
        UpdateWindow(g_hWnd);
        SetFocus(g_hWnd);
        SetForegroundWindow(g_hWnd);

        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
    
    std::vector<PhysicalObject*> ObjectReg;
    int particleCount = 2000;

    srand(clock());


    /*
    ObjectReg.push_back(new PhysicalObject(10.0, 384.0, SolarMass * Scale, eps(SolarRadius * Scale), 0, 0));
    ObjectReg[0]->ShowInfo();
    ObjectReg.push_back(new PhysicalObject(10.0 + (SolarRadius + EarthSunDistance + EarthRadius) * Scale, 384.0, EarthMass * Scale, eps(EarthRadius * Scale), 0, eps(EarthSunVelocity * Scale)));
    ObjectReg[1]->ShowInfo();
    */

    
    for (int i = 0; i < particleCount; ++i)
    {
        
        CType randX = 1 + rand() % g_iWindowWidth;
        CType randY = 1 + rand() % g_iWindowHeight;
        CType randMass = 10 + (rand() % 100) * (rand() % 1000);
        //CType randMass = 10000;
        if (i > 0)
        /*
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
        */
            ObjectReg.push_back(new PhysicalObject(randX, randY, randMass, randMass / 10000, 0, 0));
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
                if (ShowConsole)
                {
                    std::thread ConsoleThread(DebugEcho, ObjectReg);
                    //std::thread PhysicsThread(UpdatePhysics, std::ref(ObjectReg), timescale, DeviceCoreCount - 2);
                    UpdatePhysics(ObjectReg, timescale, DeviceCoreCount - 2);
                    std::thread GraphicsThread(DrawFrame, ObjectReg);
                    ConsoleThread.join();
                    GraphicsThread.join();
                    //PhysicsThread.join();
                }
                else
                {
                    UpdatePhysics(ObjectReg, timescale, DeviceCoreCount);
                    DrawFrame(ObjectReg);
                    //std::thread GraphicsThread(DrawFrame, ObjectReg);
                    //GraphicsThread.join();
                    //PhysicsThread.join();
                }
            }
            else
            {
                if (ShowConsole)
                {
                    DebugEcho(ObjectReg);
                    DrawFrame(ObjectReg);
                    UpdatePhysics(ObjectReg, timescale, 6);
                }
                else
                {
                    DrawFrame(ObjectReg);
                    UpdatePhysics(ObjectReg, timescale, 6);
                }
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

bool InitDirect3D()
{
    return 0;
}

//std::mutex GraphicsThreadMutex;

void DrawFrame(std::vector<PhysicalObject*> ObjectReg)
{

}

void Shutdown()
{
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