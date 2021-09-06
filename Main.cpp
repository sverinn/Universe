#define _WIN32_WINNT 0x600

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

#include "Renderer.h"
#include "Constants.h"
#include "Console.h"
#include <mutex>
#include "stdafx.h"
#include "Window.h"
#include "Gameloop.h"
#include <windowsx.h>
#include "Scenes.h"
#include "ObjectHandler.h"

//Переменные игры
bool ShowConsole = false;
const int DeviceCoreCount = std::thread::hardware_concurrency();
bool keys[256];
bool HT = true;
double Scale = 1e-12;
CType timescale = 5000;

//Декларации фукнкций
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow); //Точка старта приложения
double eps(double value);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int(nShowCmd))
{
    if (ShowConsole)
        CallConsole();

    Window Wnd(1600, 900, L"Universe Simulator");
    
    std::vector<PhysicalObject*> ObjectReg;
    size_t particleCount = 100;

    CreateRandomObject(Wnd, ObjectReg, particleCount);
    
    BOOL gResult;

    while (Wnd.ApplicationState())
    {
        gResult = Wnd.ProcessMessages();

        if (ShowConsole)
        {
            DoTick(Wnd, ObjectReg, timescale, HT);
            DebugEcho(ObjectReg);
        }
        else
        {
            DoTick(Wnd, ObjectReg, timescale, HT);
        }
    }

    if (gResult == -1)
    {
        return -1;
    }
    else
    {
        return Wnd.msg.wParam;
    }
}



double eps(double value)
{
    if (abs(value) < EPS)
        return 0.0;
    else
        return value;
};