//
// Created by sean on 08/08/2020.
//

#include "Agent.h"
#include "Detection.h"

// --------------------------------------------------------------------------------


// TODO lots of nasty code repetition here, do something about it

// --------------------------------------------------------------------------------

std::vector<HurtfulAgent*> DetectableComponent_Hurtful::detectableAgents = {};

unsigned int DetectableComponent_Hurtful::directionToNearest(int x, int y) {

    float shortestDistance = INT32_MAX;
    float distance;
    unsigned int unit_x = 0;
    unsigned int unit_y = 0;

    for( int n = 0; n< DetectableComponent_Hurtful::detectableAgents.size(); n++) {

        int otherX = detectableAgents[n]->alienVars.get(0);
        int otherY = detectableAgents[n]->alienVars.get(1);

        int deltaX = otherX - x;
        int deltaY = otherY - y;

        distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));

        if (distance < shortestDistance) {
            shortestDistance = distance;
            unit_x = deltaX / distance;
            unit_y = deltaY / distance;
        }
    }

    std::cout << "unit_x = " << unit_x << " unit_y = " << unit_y << std::endl;

    if (unit_x == -1 && unit_y == 0 ) return 3;
    if (unit_x == 0 && unit_y == -1 ) return 2;
    if (unit_x == 1 && unit_y == 0 ) return 1;
    if (unit_x == 0 && unit_y == 1 ) return 0;

    return -1;
}

// --------------------------------------------------------------------------------

std::vector<HealingAgent*> DetectableComponent_Healing::detectableAgents = {};

unsigned int DetectableComponent_Healing::directionToNearest(int x, int y) {

    float shortestDistance = INT32_MAX;
    float distance;
    unsigned int unit_x = 0;
    unsigned int unit_y = 0;

    for( int n = 0; n< detectableAgents.size(); n++) {

        int otherX = detectableAgents[n]->alienVars.get(0);
        int otherY = detectableAgents[n]->alienVars.get(1);

        int deltaX = otherX - x;
        int deltaY = otherY - y;

        distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));

        if (distance < shortestDistance) {
            shortestDistance = distance;
            unit_x = deltaX / distance;
            unit_y = deltaY / distance;
        }
    }

    std::cout << "unit_x = " << unit_x << " unit_y = " << unit_y << std::endl;

    if (unit_x == -1 && unit_y == 0 ) return 3;
    if (unit_x == 0 && unit_y == -1 ) return 2;
    if (unit_x == 1 && unit_y == 0 ) return 1;
    if (unit_x == 0 && unit_y == 1 ) return 0;

    return -1;
}

// --------------------------------------------------------------------------------

std::vector<PlayerAgent*> DetectableComponent_Player::detectableAgents = {};

unsigned int DetectableComponent_Player::directionToNearest(int x, int y) {

    float shortestDistance = INT32_MAX;
    float distance;
    float finalX = 0;
    float finalY = 0;
    float deltaX = 0;
    float deltaY = 0;

    for( int n = 0; n< detectableAgents.size(); n++) {

        float otherX = detectableAgents[n]->alienVars.get(0);
        float otherY = detectableAgents[n]->alienVars.get(1);

        deltaX = otherX - x;
        deltaY = otherY - y;

        distance = abs(sqrt((deltaX * deltaX) + (deltaY * deltaY)));

        if (distance < shortestDistance) {
            shortestDistance = distance;
            finalX = ceil(deltaX / distance);
            finalY = ceil (deltaY / distance);
        }
    }


    // TODO lets make this slightly more rounded...
    if ( finalX >= 1  ) {
        return 1;
    }
    if ( finalX <= -1  ) {
        return 3;
    }
    if ( finalY >= 1 ) {
        return 2;
    }
    if ( finalY <= -1 ) {
        return 0;
    }

    return -1;
}

// --------------------------------------------------------------------------------


std::vector<GoalAgent*> DetectableComponent_Goal::detectableAgents = {};

unsigned int DetectableComponent_Goal::directionToNearest(int x, int y) {

    float shortestDistance = INT32_MAX;
    float distance;
    unsigned int unit_x = 0;
    unsigned int unit_y = 0;

    for( int n = 0; n< detectableAgents.size(); n++) {

        int otherX = detectableAgents[n]->alienVars.get(0);
        int otherY = detectableAgents[n]->alienVars.get(1);

        int deltaX = otherX - x;
        int deltaY = otherY - y;

        distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));

        if (distance < shortestDistance) {
            shortestDistance = distance;
            unit_x = deltaX / distance;
            unit_y = deltaY / distance;
        }
    }

    std::cout << "unit_x = " << unit_x << " unit_y = " << unit_y << std::endl;

    if (unit_x == -1 && unit_y == 0 ) return 3;
    if (unit_x == 0 && unit_y == -1 ) return 2;
    if (unit_x == 1 && unit_y == 0 ) return 1;
    if (unit_x == 0 && unit_y == 1 ) return 0;

    return -1;
}

// --------------------------------------------------------------------------------
