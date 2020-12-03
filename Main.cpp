#include "Physics.h"
#include "Renderer.h"
#include "Window.h"
#include "ObjectHandler.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Universe Simulator");
    std::vector<PhysicalObject*> ObjectReg;

    while (window.isOpen())
    {
        UpdatePhysics(ObjectReg);
        RenderScene(window, ObjectReg);
        for (auto iObject : ObjectReg)
            iObject->ShowInfo();
    }

    return 0;
}