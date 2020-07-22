cmake_minimum_required(VERSION 3.16)
project(Glynth)

set(CMAKE_CXX_STANDARD 17)

add_executable(Glynth main.cpp
        Engine/Engine.cpp Engine/Engine.h
        Engine/Entity.cpp Engine/Entity.h
        Engine/Input.cpp Engine/Input.h
        Engine/Scheduler.cpp Engine/Scheduler.h
        Language/Lexer.cpp Language/Lexer.h
        Language/Parser.cpp Language/Parser.h
        Language/Tokens.h
        Language/Instructions.cpp Language/Instructions.h
        Language/AST.cpp Language/AST.h
        Language/Assembler.cpp Language/Assembler.h
        Language/VirtualMachine.cpp Language/VirtualMachine.h
        )


find_package(SFML REQUIRED COMPONENTS system graphics window network audio)

set(SFML_LIBRARIES "-lsfml-graphics -lsfml-window -lsfml-system")

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()