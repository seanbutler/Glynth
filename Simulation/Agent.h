//
// Created by sean on 23/07/2020.
//

#ifndef GLYNTH_AGENT_H
#define GLYNTH_AGENT_H

#include "../Engine/Entity.h"

//
// a specific version of a game entity which has AI
//

class Agent : public Entity {
public:
    Agent(std::string F, sf::Color C) : Entity()
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
        parser.OutputTreeDiagram(F);
        parser.OutputAsm(F);

        Assembler assembler(parser.GetAsm());
        assembler.Scan();
        assembler.OutputInstructionList(F);

        assembler.GenerateTestBinaryInstructions();

        virtualMachine = new VM(assembler.GetInstructions(), alienVars);

        rectangle.setFillColor(C);
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

    sf::RectangleShape rectangle;

    std::array<int, 32> alienVars;

    VM* virtualMachine;
};

#endif //GLYNTH_AGENT_H
