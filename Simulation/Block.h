//
// Created by sean on 23/07/2020.
//

#ifndef GLYNTH_BLOCK_H
#define GLYNTH_BLOCK_H

#include "../Engine/Entity.h"

//
// a static version of a game entity which has no behaviour but only visuals and collision
//

// TODO - move me to the engine, as I;m not even an agent

class Block : public Entity {
public:
    Block(sf::Color C) : Entity()
    {
        std::cout << "Block::Block ()" << std::endl;

        rectangle.setFillColor(new sf::Color(0, 0, 0));
        rectangle.setSize(sf::Vector2f (1, 1));
//        rectangle.setPosition(sf::Vector2f (1, 1));
    }

    virtual void Render(sf::RenderWindow *W){

        W->draw(rectangle);
    }

    virtual void Update(float deltaTime) {

    };

    sf::RectangleShape rectangle;
};

#endif //GLYNTH_BLOCK_H
