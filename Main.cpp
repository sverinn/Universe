#include "Physics.h"
#include "Renderer.h"
#include "ObjectHandler.h"
#include "Constants.h"

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