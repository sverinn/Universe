#include "DrawContent.h"
#include "Window.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "TimeSystem.h"
#include "ObjectHandler.h"

/*
sf::RenderWindow InitializeRenderer()
{
    
    return window;
};
*/



void RenderScene(sf::RenderWindow &targetWindow, std::vector<PhysicalObject*> &ObjectReg)
{
    sf::Event event;
    while (targetWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            targetWindow.close();
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Creating an object" << std::endl;
                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                //PhysicalObject Object(event.mouseButton.x, event.mouseButton.y);
                ObjectReg.push_back(new PhysicalObject(event.mouseButton.x, event.mouseButton.y));
                //sf::CircleShape
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            std::cout << "Input: " << std::endl;
            std::string inputString;
            std::cin >> inputString;
            if (inputString == "list_objects")
            {
                std::cout << "There are " << ObjectReg.size() << " objects in the world." << std::endl;
                for (auto i = 0; i < ObjectReg.size(); i++)
                    ObjectReg[i]->ShowInfo();
            }
        }
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Can't load the font";
    }

    sf::Text TickCounter;
    TickCounter.setFont(font);
    TickCounter.setCharacterSize(10);
    TickCounter.setFillColor(sf::Color::Green);
    TickCounter.setString(std::to_string(WorldTick()));

    //std::vector<sf::CircleShape> ObjectRenderArray;
    targetWindow.clear();
    for (auto i = 0; i < ObjectReg.size(); i++)
    {
        // if (!ObjectReg[i]->Init())
        {
            sf::CircleShape newSprite;
            //ObjectRenderArray.push_back(newSprite);
            //int radius = ObjectReg[i]->GetSize();
            newSprite.setRadius(ObjectReg[i]->GetSize());
            newSprite.setFillColor(sf::Color(200, 200, 200));
            newSprite.setPosition(ObjectReg[i]->GetX(), ObjectReg[i]->GetY());
            
            sf::Text ObjectInfo;
            ObjectInfo.setFont(font);
            ObjectInfo.setCharacterSize(10);
            ObjectInfo.setFillColor(sf::Color::Green);
            ObjectInfo.setPosition(ObjectReg[i]->GetX(), ObjectReg[i]->GetY() - 2);
            ObjectInfo.setString("ID: " + std::to_string(ObjectReg[i]->GetID())
                + ", Mass = " + std::to_string(ObjectReg[i]->GetMass())
                + ", dX = " + std::to_string(ObjectReg[i]->GetdX())
                + ", dY = " + std::to_string(ObjectReg[i]->GetdY()));

            sf::Vertex VectorLine[] =
            {
                sf::Vertex(sf::Vector2f(ObjectReg[i]->GetX() + (ObjectReg[i]->GetSize()), ObjectReg[i]->GetY() + (ObjectReg[i]->GetSize()))),
                sf::Vertex(sf::Vector2f(ObjectReg[i]->GetX() + (ObjectReg[i]->GetSize()) + (ObjectReg[i]->GetdX() * 100), ObjectReg[i]->GetY() + (ObjectReg[i]->GetSize()) + (ObjectReg[i]->GetdY() * 100)))
            };

            VectorLine->color = sf::Color::Red;

            targetWindow.draw(newSprite);
            targetWindow.draw(ObjectInfo);
            targetWindow.draw(VectorLine, 2, sf::Lines);
        }
    }
    targetWindow.draw(TickCounter);
    targetWindow.display();

};

static void RenderMenu(bool Main)
{
    if (Main)
    {

    }
};