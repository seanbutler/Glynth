//
// Created by sean on 11/06/2020.
//

#include "Engine.h"
#include <iostream>

namespace Engine {

    Engine::Engine(unsigned int W, unsigned int H, unsigned int PS, unsigned int SC, unsigned int FR)
            :   w(W)
            ,   h(H)
            ,   pixel_scale(PS)
            ,   scale(SC)
            ,   window(sf::VideoMode(w, h),
                       "GLYNTH",
                       sf::Style::Titlebar | sf::Style::Close)
    {
        window.setSize(sf::Vector2u(w*pixel_scale,h*pixel_scale));
        window.setFramerateLimit(FR);
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
        }
    }

    Engine::~Engine()
    {
    }


};
