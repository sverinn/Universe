#include "Renderer.h"
#include "Physics.h"
#include "Window.h"
#include "Objects.h"
#include "Gameloop.h"

void CreateRandomObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg)
{
    srand(clock());
    CType randX = 1.f + (rand() % Wnd.Width());
    CType randY = 1.f + (rand() % Wnd.Height());
    CType randMass = 10.f + (rand() % 1000) * (rand() % 1000);
    //CType randMass = 100000;        
    D3DXCOLOR RandRGBA = { (float)(rand() % 255),(float)(rand() % 255),(float)(rand() % 255), 1.f };

    ObjectReg.push_back(new PhysicalObject(randX, randY, randMass, randMass / 32982.53, 0, 0, RandRGBA));
}

void CreateRandomObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, int X, int Y)
{
    srand(clock());
    //CType randMass = 10.f + (rand() % 1000) * (rand() % 1000);
    CType randMass = 25000000000;
    D3DXCOLOR RandRGBA = { (float)(rand() % 255),(float)(rand() % 255),(float)(rand() % 255), 1.f };

    ObjectReg.push_back(new PhysicalObject(X, Y, randMass, 60, 0, 0, RandRGBA));
}

void CreateRandomObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, size_t particleCount)
{
    //ObjectReg.push_back(new PhysicalObject(Wnd.Width() / 2, Wnd.Height() / 2, 100000000, 80, 0, 0, { 240,240,20,200 }));
    srand(clock());
    for (int i = 0; i < particleCount; ++i)
    {
        CType randX = 1.f + (rand() % Wnd.Width());
        CType randY = 1.f + (rand() % Wnd.Height());
        CType randMass = 10.f + (rand() % 5) * (rand() % 5);
        //CType randMass = 100000;        
        D3DXCOLOR RandRGBA = { (float)(rand() % 255),(float)(rand() % 255),(float)(rand() % 255), 1.f };
        //if (i > 0)
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
        ObjectReg.push_back(new PhysicalObject(randX, randY, randMass, randMass, 0, 0, RandRGBA));
    }
}

void CreateRandomAcceleratedObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, size_t particleCount)
{
    //ObjectReg.push_back(new PhysicalObject(Wnd.Width() / 2, Wnd.Height() / 2, 100000000, 80, 0, 0, { 240,240,20,200 }));
    srand(clock());
    for (int i = 0; i < particleCount; ++i)
    {
        CType randX = 1.f + (rand() % Wnd.Width());
        CType randY = 1.f + (rand() % Wnd.Height());
        CType randMass = 10.f + (rand() % 1000) * (rand() % 100);
        //CType randMass = 100000;        
        D3DXCOLOR RandRGBA = { (float)(rand() % 255),(float)(rand() % 255),(float)(rand() % 255), 1.f };
        //if (i > 0)
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
        ObjectReg.push_back(new PhysicalObject(randX, randY, randMass, randMass / 32982.53, rand() % 5 - 2.5, rand() % 2 - 2.5, RandRGBA));
    }
}