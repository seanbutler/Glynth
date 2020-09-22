cmake_minimum_required(VERSION 3.16)
project(Glynth)

set(CMAKE_CXX_STANDARD 17)

add_executable(Glynth main.cpp
        Engine/Engine.cpp
        Engine/Engine.h
        Engine/Entity.h
        Engine/Input.h
        Engine/Scheduler.h
        Genetics/Evolution.cpp
        Genetics/Evolution.h
        Genetics/Mutations/MutationVisitor.h
        Genetics/Mutations/MutationVisitor.cpp
        Genetics/Mutations/Mutagen.h
        Genetics/Mutations/Mutagen.cpp
        Language/Instructions.cpp
        Language/Instructions.h
        Language/Lexer.cpp
        Language/Lexer.h
        Language/AST.cpp
        Language/AST.h
        Language/Parser.cpp
        Language/Parser.h
        Language/Tokens.h
        Language/Assembler.cpp
        Language/Assembler.h
        Language/VirtualMachine.cpp
        Language/VirtualMachine.h
        Simulation/Agent.h
        Simulation/Agent.cpp
        Simulation/Detection.h
        Simulation/Detection.cpp
        Utils/Maze.h

        Test/SeanTest.h
        Test/SeanTest.cpp

        Utils/RandomNumberGenerator.cpp
        Utils/RandomNumberGenerator.h

        Test/TobyTest.h
        Test/TobyTest.cpp

        Test/PlayerAgentTest.h
        Test/PlayerAgentTest.cpp

        )


find_package(SFML REQUIRED COMPONENTS system graphics window network audio)

set(SFML_LIBRARIES "-lsfml-graphics -lsfml-window -lsfml-system")

TARGET_LINK_LIBRARIES(Glynth pthread)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()