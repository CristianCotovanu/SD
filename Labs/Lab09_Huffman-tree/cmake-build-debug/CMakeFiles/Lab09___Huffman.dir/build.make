# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /opt/clion-2018.3.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.3.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Lab09___Huffman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab09___Huffman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab09___Huffman.dir/flags.make

CMakeFiles/Lab09___Huffman.dir/test.c.o: CMakeFiles/Lab09___Huffman.dir/flags.make
CMakeFiles/Lab09___Huffman.dir/test.c.o: ../test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Lab09___Huffman.dir/test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Lab09___Huffman.dir/test.c.o   -c "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman/test.c"

CMakeFiles/Lab09___Huffman.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Lab09___Huffman.dir/test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman/test.c" > CMakeFiles/Lab09___Huffman.dir/test.c.i

CMakeFiles/Lab09___Huffman.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Lab09___Huffman.dir/test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman/test.c" -o CMakeFiles/Lab09___Huffman.dir/test.c.s

# Object files for target Lab09___Huffman
Lab09___Huffman_OBJECTS = \
"CMakeFiles/Lab09___Huffman.dir/test.c.o"

# External object files for target Lab09___Huffman
Lab09___Huffman_EXTERNAL_OBJECTS =

Lab09___Huffman: CMakeFiles/Lab09___Huffman.dir/test.c.o
Lab09___Huffman: CMakeFiles/Lab09___Huffman.dir/build.make
Lab09___Huffman: CMakeFiles/Lab09___Huffman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Lab09___Huffman"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab09___Huffman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab09___Huffman.dir/build: Lab09___Huffman

.PHONY : CMakeFiles/Lab09___Huffman.dir/build

CMakeFiles/Lab09___Huffman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab09___Huffman.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab09___Huffman.dir/clean

CMakeFiles/Lab09___Huffman.dir/depend:
	cd "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman" "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman" "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman/cmake-build-debug" "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman/cmake-build-debug" "/home/student/Desktop/Anul 1/Sem 2/SD/Lab09 - Huffman/cmake-build-debug/CMakeFiles/Lab09___Huffman.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Lab09___Huffman.dir/depend
