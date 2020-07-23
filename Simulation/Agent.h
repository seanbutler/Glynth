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
//        std::string filename = "Assets/agent3.lang";
        std::cout << "Agent::Agent (" << F << ")" << std::endl;
//        alienVars["x"] = 0;
//        alienVars["y"] = 0;

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

        virtualMachine = new VM(assembler.GetInstructions());

        rectangle.setFillColor(C);
        rectangle.setSize(sf::Vector2f (1, 1));
    }

    virtual void Render(sf::RenderWindow *W){
        rectangle.setPosition(alienVars["x"], alienVars["y"]);
        W->draw(rectangle);
    }

    void SetAlienVar(std::string name, int value) {
        alienVars[name] = value;
    }

    virtual void Update(float deltaTime) {
        virtualMachine->Execute();
    };

    sf::RectangleShape rectangle;
    std::map<std::string, int> alienVars;

    VM* virtualMachine;
};

#endif //GLYNTH_AGENT_H
