//
// Created by sean on 23/07/2020.
//

#pragma once

#include <cmath>
#include "../Engine/Entity.h"

#include "../Language/Lexer.h"
#include "../Language/Parser.h"
#include "../Language/Assembler.h"
#include "../Language/VirtualMachine.h"

#include "AlienVars.h"

//
// a specific version of a game entity which has AI
//

// ----------------------------------------------------------------------


class AgentType {
public:
    AgentType(sf::Color C)
    :   colour(C) {

    }

    sf::Color  Colour()         { return colour;}

protected:
    const sf::Color colour;
};

// ----------------------------------------------------------------------

class DetectableAgentType : public AgentType {

public:
    DetectableAgentType(sf::Color C)
            : AgentType(C)
    {
    }

public:
    unsigned int directionToNearest(int x, int y) {

        unsigned int shortestDistance = INT32_MAX;
        float distance;
        unsigned int closest = INT32_MAX;

        for( int n = 0; n< positionTable.size(); n++) {

            distance =  sqrt ( ( ( positionTable[n].first - x ) * ( positionTable[n].first - x ) )
                               + ( ( positionTable[n].second - y ) * ( positionTable[n].second - y ) ) );

            if ( distance < shortestDistance ) {
                shortestDistance = distance;
                closest = n;
            }

            int unitx = ( positionTable[n].first - x ) / distance;
            int unity = ( positionTable[n].second - y ) / distance;

            std::cout << "unity = " << unitx << "unity = " << unity << std::endl;

            if ( unitx == -1 && unity == 0 ) return 3;
            if ( unitx == 0 && unity == -1 ) return 2;
            if ( unitx == 1 && unity == 0 ) return 1;
            if ( unitx == 0 && unity == 1 ) return 0;
        }
    }

private:
    static std::vector<std::pair<int, int>> positionTable;
    std::vector<int> distanceTable;

};

// ----------------------------------------------------------------------

class PlayerAgentType : public DetectableAgentType {
    // Grey is anonymous, like a good player character
    // Movable, Hurtable
    //
public:
    PlayerAgentType()
    : DetectableAgentType(sf::Color(128, 128, 128))
    {

    }

};

// ----------------------------------------------------------------------

class GoalAgentType : public DetectableAgentType {
    // Nice Sky Colour for Escape?
    // End of Game
public:
    GoalAgentType()
        : DetectableAgentType(sf::Color(128, 192, 255))
    {
    }

};

// ----------------------------------------------------------------------

class HealingAgentType : public DetectableAgentType {
    // Green, Like a Healthpack
    // Touch and it heals you
public:
    HealingAgentType()
            : DetectableAgentType(sf::Color(32, 255, 32))
    {
    }


};

// ----------------------------------------------------------------------


class HurtfulAgentType : public DetectableAgentType {
    // Red is Danger
    // Touch and it hurts you
public:
    HurtfulAgentType()
    : DetectableAgentType(sf::Color(255, 32, 32))
    {

    }


};

// ----------------------------------------------------------------------


class WallAgentType : public AgentType {
    // Walls are Black
    // Impassible
public:
    WallAgentType()
            : AgentType(sf::Color(0, 0, 0))
    {

    }

};

// ----------------------------------------------------------------------

class Agent : public Engine::Entity {
public:
    Agent(AgentType AT)
            : Entity()
            , agenttype(AT) {
        std::cout << "Agent::Agent ()" << std::endl;
        rectangle.setFillColor(agenttype.Colour());
        rectangle.setSize(sf::Vector2f (1, 1));
    }

    Agent(Agent &rhs)
    : agenttype(rhs.agenttype.Colour()),
        srcFilename(rhs.srcFilename),
        rectangle(rhs.rectangle),
        lexer(rhs.lexer),
        parser(rhs.parser),
        assembler(rhs.assembler),
        virtualMachine(rhs.virtualMachine),
        alienVars(rhs.alienVars)
    {
        virtualMachine.SetAliensVarPtr(&alienVars);
    }

    virtual void Compile(std::string F) {
        srcFilename = F;
        std::ifstream sourceFile(srcFilename);
        std::string sourceString((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

        lexer.SetSourceString(sourceString, 0);
        lexer.Scan();
        lexer.OutputTokenList(srcFilename);
        lexer.OutputTokenListWithLines(srcFilename);
        //        parser.SetTokens(lexer.GetTokenList());
        parser.SetTokensWithLines(lexer.GetTokenListWithLines());
        parser.parse();

        parser.OutputTreeDiagram(srcFilename);
        parser.OutputAsm(srcFilename);
        parser.OutputASTJSON(srcFilename);
    }

    virtual void Assemble()
    {
        assembler.Scan(parser.GetAsm());
        assembler.OutputInstructionList(srcFilename);

        assembler.GenerateTestBinaryInstructions();
        virtualMachine.Initialise(assembler.GetInstructions(), &alienVars);
    }

    virtual void Render(sf::RenderWindow *W){
        if (!virtualMachine.done){
            rectangle.setPosition(alienVars.get(0), alienVars.get(1));
            W->draw(rectangle);
        }
    }

    void SetAlienVar(int id, int value) {
        alienVars.set(id, value);
    }

    int GetAlienVar(int id) {
        return alienVars.get(id);
    }

    virtual void Update(float deltaTime) {
        if (!virtualMachine.done) {
            virtualMachine.Execute(10);
        }
    };

    Agent* Cross(Agent* agent){
        // Copy this agent
        auto newAgent = new Agent(*this);

        // Find the two slice points
        ASTNode** a = newAgent->parser.GetRandomASTNode(CompatibilityType::all);
        ASTNode* aP = *a;
        ASTNode** b = agent->parser.GetRandomASTNode((*a)->GetCompType());

        // Replace the nodes after the first slice point with the branch of the second
        if(b != nullptr)
        {
            newAgent->parser.CopyNodeAndChildren(*b, *a);
            parser.DeleteNodeAndChildren(aP);
        }

        return newAgent;
    }

    std::string srcFilename;
    AgentType agenttype;
    sf::RectangleShape rectangle;

    Lexer lexer;
    Parser parser;
    Assembler assembler;
    VM virtualMachine;

    AlienVars alienVars;

};

// ----------------------------------------------------------------------
