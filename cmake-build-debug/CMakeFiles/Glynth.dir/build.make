# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/114/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/114/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sean/Projects/Glynth

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sean/Projects/Glynth/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Glynth.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Glynth.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Glynth.dir/flags.make

CMakeFiles/Glynth.dir/main.cpp.o: CMakeFiles/Glynth.dir/flags.make
CMakeFiles/Glynth.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sean/Projects/Glynth/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Glynth.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Glynth.dir/main.cpp.o -c /home/sean/Projects/Glynth/main.cpp

CMakeFiles/Glynth.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Glynth.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sean/Projects/Glynth/main.cpp > CMakeFiles/Glynth.dir/main.cpp.i

CMakeFiles/Glynth.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Glynth.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sean/Projects/Glynth/main.cpp -o CMakeFiles/Glynth.dir/main.cpp.s

CMakeFiles/Glynth.dir/Language/Lexer.cpp.o: CMakeFiles/Glynth.dir/flags.make
CMakeFiles/Glynth.dir/Language/Lexer.cpp.o: ../Language/Lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sean/Projects/Glynth/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Glynth.dir/Language/Lexer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Glynth.dir/Language/Lexer.cpp.o -c /home/sean/Projects/Glynth/Language/Lexer.cpp

CMakeFiles/Glynth.dir/Language/Lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Glynth.dir/Language/Lexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sean/Projects/Glynth/Language/Lexer.cpp > CMakeFiles/Glynth.dir/Language/Lexer.cpp.i

CMakeFiles/Glynth.dir/Language/Lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Glynth.dir/Language/Lexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sean/Projects/Glynth/Language/Lexer.cpp -o CMakeFiles/Glynth.dir/Language/Lexer.cpp.s

CMakeFiles/Glynth.dir/Language/Parser.cpp.o: CMakeFiles/Glynth.dir/flags.make
CMakeFiles/Glynth.dir/Language/Parser.cpp.o: ../Language/Parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sean/Projects/Glynth/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Glynth.dir/Language/Parser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Glynth.dir/Language/Parser.cpp.o -c /home/sean/Projects/Glynth/Language/Parser.cpp

CMakeFiles/Glynth.dir/Language/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Glynth.dir/Language/Parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sean/Projects/Glynth/Language/Parser.cpp > CMakeFiles/Glynth.dir/Language/Parser.cpp.i

CMakeFiles/Glynth.dir/Language/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Glynth.dir/Language/Parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sean/Projects/Glynth/Language/Parser.cpp -o CMakeFiles/Glynth.dir/Language/Parser.cpp.s

CMakeFiles/Glynth.dir/Language/AST.cpp.o: CMakeFiles/Glynth.dir/flags.make
CMakeFiles/Glynth.dir/Language/AST.cpp.o: ../Language/AST.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sean/Projects/Glynth/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Glynth.dir/Language/AST.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Glynth.dir/Language/AST.cpp.o -c /home/sean/Projects/Glynth/Language/AST.cpp

CMakeFiles/Glynth.dir/Language/AST.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Glynth.dir/Language/AST.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sean/Projects/Glynth/Language/AST.cpp > CMakeFiles/Glynth.dir/Language/AST.cpp.i

CMakeFiles/Glynth.dir/Language/AST.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Glynth.dir/Language/AST.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sean/Projects/Glynth/Language/AST.cpp -o CMakeFiles/Glynth.dir/Language/AST.cpp.s

# Object files for target Glynth
Glynth_OBJECTS = \
"CMakeFiles/Glynth.dir/main.cpp.o" \
"CMakeFiles/Glynth.dir/Language/Lexer.cpp.o" \
"CMakeFiles/Glynth.dir/Language/Parser.cpp.o" \
"CMakeFiles/Glynth.dir/Language/AST.cpp.o"

# External object files for target Glynth
Glynth_EXTERNAL_OBJECTS =

Glynth: CMakeFiles/Glynth.dir/main.cpp.o
Glynth: CMakeFiles/Glynth.dir/Language/Lexer.cpp.o
Glynth: CMakeFiles/Glynth.dir/Language/Parser.cpp.o
Glynth: CMakeFiles/Glynth.dir/Language/AST.cpp.o
Glynth: CMakeFiles/Glynth.dir/build.make
Glynth: CMakeFiles/Glynth.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sean/Projects/Glynth/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Glynth"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Glynth.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Glynth.dir/build: Glynth

.PHONY : CMakeFiles/Glynth.dir/build

CMakeFiles/Glynth.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Glynth.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Glynth.dir/clean

CMakeFiles/Glynth.dir/depend:
	cd /home/sean/Projects/Glynth/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sean/Projects/Glynth /home/sean/Projects/Glynth /home/sean/Projects/Glynth/cmake-build-debug /home/sean/Projects/Glynth/cmake-build-debug /home/sean/Projects/Glynth/cmake-build-debug/CMakeFiles/Glynth.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Glynth.dir/depend

