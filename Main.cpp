#define _WIN32_WINNT 0x600


#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")


#include "Renderer.h"
#include "Constants.h"
#include "Console.h"
#include <string>
#include <thread>
#include <mutex>
#include "stdafx.h"
#include "Window.h"
#include "Gameloop.h"

//Переменные игры
bool ShowConsole = true;
const int DeviceCoreCount = std::thread::hardware_concurrency();
bool keys[256];
bool HT = true;
double Scale = 1e-7;
CType timescale = 50;

//Декларации фукнкций
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow); //Точка старта приложения
void DebugEcho(std::vector<PhysicalObject*> ObjectReg);
double eps(double value);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int(nShowCmd))
{
    if (ShowConsole)
        CallConsole();

    Window Wnd(1600, 900, L"Universe Simulator");
    
    std::vector<PhysicalObject*> ObjectReg;
    size_t particleCount = 3000;

    CreateRandomObjects(Wnd, ObjectReg, particleCount);
    
    BOOL gResult;

    while (true)
    {
        Wnd.ProcessMessages();
        if (ShowConsole)
        {
            DoTick(Wnd, ObjectReg, timescale, HT);
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