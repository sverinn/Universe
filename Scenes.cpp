#include "Renderer.h"
#include "Physics.h"
#include "Window.h"
#include "Objects.h"
#include "Gameloop.h"

void SolarSystem(Window Wnd, std::vector<PhysicalObject*> ObjectReg)
{
	D3DXCOLOR RGBA = { 255.f,255.f, 0.f, 1.f };
	ObjectReg.push_back(new PhysicalObject(Wnd.Width() / 2, Wnd.Height() / 2, SolarMass, SolarMass / 32982.53, rand() % 5 - 2.5, rand() % 2 - 2.5, RGBA));
}

