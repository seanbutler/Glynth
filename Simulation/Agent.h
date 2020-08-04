//
// Created by sean on 23/07/2020.
//

#ifndef GLYNTH_AGENT_H
#define GLYNTH_AGENT_H

#include "../Engine/Entity.h"

#include "../Language/Lexer.h"
#include "../Language/Parser.h"
#include "../Language/Assembler.h"
#include "../Language/VirtualMachine.h"

#include "AlienVars.h"


//
// a specific version of a game entity which has AI
//

enum class AgentTypeEnum {
    Player,
    Goal,
    Healing,
    Hurtful,
    Wall
};

class AgentType {
public:
    AgentType(AgentTypeEnum AT, sf::Color C)
    : agentType(AT)
    , colour(C) {

    }

    AgentTypeEnum Type(){ return agentType;}
    sf::Color  Colour(){ return colour;}

protected:
    const AgentTypeEnum agentType;
    const sf::Color colour;
};

class PlayerAgentType : public AgentType {
    // Grey is anonymous, like a good player character
    // Movable
    // Hurtable
public:
    PlayerAgentType()
    : AgentType(AgentTypeEnum::Player, sf::Color(128, 128, 128))
    {

    }
};

class GoalAgentType : public AgentType {
    // Nice Sky Colour for Escape?
    // End of Game
public:
    GoalAgentType()
    : AgentType(AgentTypeEnum::Goal, sf::Color(128, 192, 255))
    {

    }
};

class HealingAgentType : public AgentType {
    // Green, Like a Healthpack
    // Touch and it heals you
public:
    HealingAgentType()
    : AgentType(AgentTypeEnum::Healing, sf::Color(32, 255, 32))
    {

    }
};

class HurtfulAgentType : public AgentType {
    // Red is Danger
    // Touch and it hurts you
public:
    HurtfulAgentType()
    : AgentType(AgentTypeEnum::Hurtful, sf::Color(255, 32, 32))
    {

    }
};


class WallAgentType : public AgentType {
    // Walls are Black
    // Impassible
public:
    WallAgentType()
            : AgentType(AgentTypeEnum::Wall, sf::Color(0, 0, 0))
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

    virtual void Compile(std::string F) {
        srcFilename = F;
        std::ifstream sourceFile(srcFilename);
        std::string sourceString((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

        lexer.SetSourceString(sourceString, 0);
        lexer.Scan();
        lexer.OutputTokenList(srcFilename);
        lexer.OutputTokenListWithLines(srcFilename);
        parser.SetTokens(lexer.GetTokenList());
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

#endif //GLYNTH_AGENT_H
