#include "Renderer.h"
#include "Physics.h"
#include "Window.h"
#include "Objects.h"
#include "Gameloop.h"


void DoTick(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, CType timescale, bool HT)
{
    //srand(clock());
    //Wnd.Gfx().ClearBuffer(163.f, 100.f, 3.f);
    std::thread RendererThread(RenderFrame, std::ref(Wnd.Gfx()), ObjectReg);
    std::thread PhysicsThread(UpdatePhysics, std::ref(ObjectReg), timescale, HT);
    RendererThread.join();
    PhysicsThread.join();
    //Wnd.Gfx().EndFrame();
}