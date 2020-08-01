
## Project Files & Directories Overview

### Documentation/

Automatically generate by Doxygen.
 - There is a Doxyfile in the main dir, best if you have graphviz/dot installed. Dun using doxygen Doxfile from the root dir of the project.
 - Todo integrate to the build somehow?
 - NOTE: Do not submit output to the repo

### Assets/

Various source files in a c-like language that is compiled to a tree for genetic manipulation, mutation and crossover etc.
 - has errors but is sufficient for our purposes right now.

### Engine/

Simple SFML Entity Scheduler Framework for realtime applications like games. Working but Limited in Scope.
 - Opens Windows
 - Visits Entities
 - Gets Keyboard Input

### Genetics/

Tree Operations Which can be applied to nodes or tree to adjust their contents.
 - Mutator
     - Applies a mutation over a tree according to a scheme
 - MutationVisitor
     - Specific Change, e.g. adjust a number up or down by 1
 - Scheme
     - Probability and other constraints which limit the application of a mutation

 ### Language/

Compiler which outputs bytecode and various intermediary files for a simple virtual machine.
 - c-like language
 - separate and clear lexer, parser, ast and assembler
 - simple enough to understand and easy to extend for GP as needed
 - no real types
 - outputs graphviz diagrams of AST during compilation
 - TODO : save ast and reload it for use with tree mutation code

 ### Notes/

 - notes on sytem architecture
 - discussion of criteria for GP and gameplay
 - notes on language design to facilitate GP

 ### Simulation/

 - Interface between Language and Engine
 - e.g Agent is an Entity (from Engine) whcih also has a VM (from Language) with some alienvars as an interface between
    - Inc Global/Alien Variables
    - Factory Classes
 - Specific Game Entities necessary for GP for games

### Utils/

- Independent ADTs not tied to our code but used.
- e.g. Maze Generator which operate over simple data types like arrays of bools.

