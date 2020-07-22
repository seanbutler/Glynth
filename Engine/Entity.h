//
// Created by sean on 11/06/2020.
//

#ifndef SYNTH_ENTITY_H
#define SYNTH_ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity() {}
    virtual void Update(float deltaTime) = 0;
    virtual void Render(sf::RenderWindow *W) = 0;
    virtual ~Entity() {};
};


#endif //SYNTH_ENTITY_H
