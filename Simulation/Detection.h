//
// Created by sean on 08/08/2020.
//

#pragma once

#include <cmath>

#include "../Engine/Entity.h"

#include "../Language/Lexer.h"
#include "../Language/Parser.h"
#include "../Language/Assembler.h"
#include "../Language/VirtualMachine.h"

#include "./Agent.h"
#include "AlienVars.h"

//
// a specific version of a game entity which has AI
//

// ----------------------------------------------------------------------

class DetectionComponent {
public:
    DetectionComponent(Agent& A)
    :   agent(A)
    {
    }

public:

    unsigned int directionToNearest(AgentType & AT) {

        unsigned int shortestDistance = INT32_MAX;
        float distance;
        unsigned int closest = INT32_MAX;

        int x = agent.alienVars.get(0);
        int y = agent.alienVars.get(1);

        for( int n = 0; n< positionTable.size(); n++) {

            distance =  sqrt ( ( ( std::get<0>(positionTable[n]) - x ) * ( std::get<0>(positionTable[n]) - x ) )
                               + ( ( std::get<1>(positionTable[n]) - y ) * ( std::get<1>(positionTable[n]) - y ) ) );

            if ( distance < shortestDistance ) {
                shortestDistance = distance;
                closest = n;
            }

            int unit_x = (std::get<0>(positionTable[n]) - x ) / distance;
            int unit_y = (std::get<1>(positionTable[n]) - y ) / distance;

            std::cout << "unit_y = " << unit_x << "unit_y = " << unit_y << std::endl;

            if (unit_x == -1 && unit_y == 0 ) return 3;
            if (unit_x == 0 && unit_y == -1 ) return 2;
            if (unit_x == 1 && unit_y == 0 ) return 1;
            if (unit_x == 0 && unit_y == 1 ) return 0;

        }
        return 0;
    }

    virtual void setPosition(int x, int y) {
        positionTable.emplace_back(std::tuple<int, int, AgentType>(x, y));
    }

private:
    static std::vector<std::tuple<int, int, AgentType>> positionTable;

private:
    Agent & agent;

};



