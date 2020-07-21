cmake_minimum_required(VERSION 3.16)
project(Glynth)

set(CMAKE_CXX_STANDARD 17)

add_executable(Glynth main.cpp Language/Lexer.cpp Language/Lexer.h
        Language/Parser.cpp Language/Parser.h
        Language/Tokens.h
        Language/Instructions.cpp
        Language/Instructions.h
        Language/AST.cpp Language/AST.h
        Language/Assembler.cpp Language/Assembler.h
        Language/VirtualMachine.cpp Language/VirtualMachine.h
        )