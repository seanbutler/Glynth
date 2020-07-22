//
// Created by sean on 11/06/2020.
//

#include "Engine.h"
#include <iostream>

Engine::Engine(unsigned int W, unsigned int H, unsigned int PS, unsigned int SC)
:   w(W)
,   h(H)
,   pixel_scale(PS)
,   scale(SC)
        ,   window(sf::VideoMode(w, h),
                   "game window!",
                   sf::Style::Titlebar | sf::Style::Close)
//,   guiWindow(sf::VideoMode(w, h),
//           "gui window!",
//           sf::Style::Titlebar | sf::Style::Resize)
{
    window.setSize(sf::Vector2u(w*pixel_scale,h*pixel_scale));
    window.setFramerateLimit(16);

//    if (!font.loadFromFile("./Assets/open-sans.light.ttf"))
//    {
//        std::cout << "ERROR - font missing" << std::endl;
//    }
//
//    guiWindow.setSize(sf::Vector2u(640,480));
//    guiWindow.setFramerateLimit(60);
}

void Engine::MainLoop()
{
    while (window.isOpen())
    {
        deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        entityScheduler.Update(deltaTime);

        window.clear(sf::Color(255, 255, 255, 255));
        entityScheduler.Render(&window);
        window.display();


//        sf::Event guiEvent;
//        while (guiWindow.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                guiWindow.close();
//            }
//        }

//        sf::Text text;
//
//        text.setFont(font); // font is a sf::Font
//        text.setString("Hello world");
//        text.setCharacterSize(128); // in pixels, not points!
//        text.setScale(1.0/24.0, 1.0/24.0);
//
//        text.setFillColor(sf::Color::White);
//        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
//        guiWindow.clear(sf::Color(64, 64, 64, 255));
//        guiWindow.draw(text);
//        guiWindow.display();
    }
}

Engine::~Engine()
{
}
