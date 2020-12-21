#include "Renderer.h"
#include "Physics.h"
#include "Window.h"
#include "Objects.h"



void CreateRandomObjects(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg,  size_t particleCount)
{
    ObjectReg.push_back(new PhysicalObject(Wnd.Width() / 2, Wnd.Height() / 2, 100000000, 80, 0, 0, { 240,240,20,200 }));
    srand(clock());
    for (int i = 1; i < particleCount; ++i)
    {
        CType randX = 1.f + rand() % Wnd.Width();
        CType randY = 1.f + rand() % Wnd.Height();
        CType randMass = 10.f + (rand() % 100) * (rand() % 1000);
        D3DXCOLOR RandRGBA = { (float)(rand() % 255),(float)(rand() % 255),(float)(rand() % 255),(float)(rand() % 100) };
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
            ObjectReg.push_back(new PhysicalObject(randX, randY, randMass, randMass / 10000, 0, 0, RandRGBA));
    }
}

void DoTick(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, CType timescale, bool HT)
{
    //srand(clock());
    //Wnd.Gfx().ClearBuffer(163.f, 100.f, 3.f);
    RenderFrame(Wnd.Gfx(), ObjectReg);
    UpdatePhysics(ObjectReg, timescale, HT);
    //Wnd.Gfx().EndFrame();
}