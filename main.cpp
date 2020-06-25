#include <iostream>
#include <fstream>

#include "./Language/Lexer.h"
#include "./Language/Parser.h"

int main(int argc, char **argv) {
    std::cout << "GLYNTH - Game Language Program Synthesis" << std::endl;

//    srand(time(0));

    std::string filename = "Assets/agent2.lang";
    std::ifstream sourceFile(filename);
    std::string sourceString((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

    Lexer lexer(sourceString);
    lexer.Scan();
    lexer.OutputTokenList(filename);

    Parser parser(lexer.GetTokenList());
    parser.parse();
    parser.debug(filename);

    return 0;
}
