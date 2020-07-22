//
// Created by sean on 11/06/2020.
//

#ifndef SYNTH_SCHEDULER_H
#define SYNTH_SCHEDULER_H

#include <vector>
#include <memory>

#include "Entity.h"

class Scheduler {

public:
    Scheduler() {}
    virtual ~Scheduler() {}

    virtual void Update(float deltaTime)
    {
        for (auto entity : entities)
        {
            entity->Update(deltaTime);
        }
    }

    virtual void Render(sf::RenderWindow *W)
    {
        for (auto entity : entities)
        {
            entity->Render(W);
        }
    }

    std::vector<Entity*> entities;
};


#endif //SYNTH_SCHEDULER_H
