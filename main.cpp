#include <iostream>
#include <fstream>

#include "./Engine/Engine.h"

#include "./Language/Lexer.h"
#include "./Language/Parser.h"
#include "./Language/Assembler.h"
#include "./Language/VirtualMachine.h"

int main(int argc, char **argv) {
    std::cout << "GLYNTH - Game Language Program Synthesis" << std::endl;


    Engine engine;

    std::string filename = "Assets/agent2.lang";
    std::ifstream sourceFile(filename);
    std::string sourceString((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
    std::cout << sourceString << std::endl;

    Lexer lexer(sourceString);
    lexer.Scan();
    lexer.OutputTokenList(filename);

    Parser parser(lexer.GetTokenList());
    parser.parse();
    parser.OutputTreeDiagram(filename);
    parser.OutputAsm(filename);

    Assembler assembler(parser.GetAsm());
    assembler.Scan();
    assembler.OutputInstructionList(filename);

//    assembler.GenerateTestBinaryInstructions();

    VM virtualMachine(assembler.GetInstructions());
    virtualMachine.Execute();

    engine.MainLoop();
    return 0;
}
