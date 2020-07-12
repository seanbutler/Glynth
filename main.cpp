#include <iostream>
#include <fstream>

#include "./Language/Lexer.h"
#include "./Language/Parser.h"
#include "./Language/Assembler.h"
#include "./Language/VirtualMachine.h"

int main(int argc, char **argv) {
    std::cout << "GLYNTH - Game Language Program Synthesis" << std::endl;

    std::string filename = "Assets/agent1.lang";
    std::ifstream sourceFile(filename);
    std::string sourceString((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

    Lexer lexer(sourceString);
    lexer.Scan();
    lexer.OutputTokenList(filename);

    Parser parser(lexer.GetTokenList());
    parser.parse();
    parser.OutputTreeDiagram(filename);
    parser.OutputAsm(filename);

//    Assembler assembler(parser.getAST());
//    VM virtualMachine(assembler.GetBinaryInstructions());
//    virtualMachine.Execute();

    return 0;
}
