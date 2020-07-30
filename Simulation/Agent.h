//
// Created by sean on 23/07/2020.
//

#ifndef GLYNTH_AGENT_H
#define GLYNTH_AGENT_H

#include "../Engine/Entity.h"

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
public:
    PlayerAgentType()
    : AgentType(AgentTypeEnum::Player, sf::Color(128, 128, 128))
    {

    }
};

class GoalAgentType : public AgentType {
    // Nice Sky Colour for Escape?
public:
    GoalAgentType()
    : AgentType(AgentTypeEnum::Goal, sf::Color(192, 255, 255))
    {

    }
};

class HealingAgentType : public AgentType {
    // Green, Like a Healthpack
public:
    HealingAgentType()
    : AgentType(AgentTypeEnum::Healing, sf::Color(32, 255, 32))
    {

    }
};

class HurtfulAgentType : public AgentType {
    // Red is Danger
public:
    HurtfulAgentType()
    : AgentType(AgentTypeEnum::Hurtful, sf::Color(255, 32, 32))
    {

    }
};


class WallAgentType : public AgentType {
    // Walls are Black
public:
    WallAgentType()
            : AgentType(AgentTypeEnum::Wall, sf::Color(0, 0, 0))
    {

    }
};


// ----------------------------------------------------------------------

class Agent : public Engine::Entity {
public:
    Agent(std::string F, AgentType AT)
    : Entity()
    , agenttype(AT)
    {
        std::cout << "Agent::Agent (" << F << ")" << std::endl;

        std::ifstream sourceFile(F);
        std::string sourceString((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

//        std::cout << sourceString << std::endl;

        Lexer lexer(sourceString);
        lexer.Scan();
        lexer.OutputTokenList(F);

        Parser parser(lexer.GetTokenList());
        parser.parse();

        // THIS IS WHERE WE WOULD DO THE MUTATIONS...

        parser.OutputTreeDiagram(F);
        parser.OutputAsm(F);

        parser.OutputASTJSON(F);

        Assembler assembler(parser.GetAsm());
        assembler.Scan();
        assembler.OutputInstructionList(F);

        assembler.GenerateTestBinaryInstructions();

        virtualMachine = new VM(assembler.GetInstructions(), alienVars);

        rectangle.setFillColor(agenttype.Colour());
        rectangle.setSize(sf::Vector2f (1, 1));
    }

    virtual void Render(sf::RenderWindow *W){
        if (!virtualMachine->done){
            rectangle.setPosition(alienVars[0], alienVars[1]);
            W->draw(rectangle);
        }
    }

    void SetAlienVar(int id, int value) {
        alienVars[id] = value;
    }

    int GetAlienVar(int id) {
        return alienVars[id];
    }

    virtual void Update(float deltaTime) {
        if (!virtualMachine->done) {
            virtualMachine->Execute(10);
        }
    };

    AgentType agenttype;
    sf::RectangleShape rectangle;

    std::array<int, 32> alienVars;

    VM* virtualMachine;
};

// ----------------------------------------------------------------------


#endif //GLYNTH_AGENT_H
