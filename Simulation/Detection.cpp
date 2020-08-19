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

    std::cout << "unit_y = " << unit_x << "unit_y = " << unit_y << std::endl;

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

    std::cout << "unit_y = " << unit_x << "unit_y = " << unit_y << std::endl;

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

    std::cout << "unit_y = " << unit_x << "unit_y = " << unit_y << std::endl;

    if (unit_x == -1 && unit_y == 0 ) return 3;
    if (unit_x == 0 && unit_y == -1 ) return 2;
    if (unit_x == 1 && unit_y == 0 ) return 1;
    if (unit_x == 0 && unit_y == 1 ) return 0;

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

    std::cout << "unit_y = " << unit_x << "unit_y = " << unit_y << std::endl;

    if (unit_x == -1 && unit_y == 0 ) return 3;
    if (unit_x == 0 && unit_y == -1 ) return 2;
    if (unit_x == 1 && unit_y == 0 ) return 1;
    if (unit_x == 0 && unit_y == 1 ) return 0;

    return -1;
}

// --------------------------------------------------------------------------------
