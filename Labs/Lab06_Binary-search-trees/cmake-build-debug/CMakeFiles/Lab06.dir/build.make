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
CMAKE_SOURCE_DIR = "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Lab06.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab06.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab06.dir/flags.make

CMakeFiles/Lab06.dir/BSTList.c.o: CMakeFiles/Lab06.dir/flags.make
CMakeFiles/Lab06.dir/BSTList.c.o: ../BSTList.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/student/Desktop/Anul 1/Sem 2/SD/Lab06/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Lab06.dir/BSTList.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Lab06.dir/BSTList.c.o   -c "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06/BSTList.c"

CMakeFiles/Lab06.dir/BSTList.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Lab06.dir/BSTList.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06/BSTList.c" > CMakeFiles/Lab06.dir/BSTList.c.i

CMakeFiles/Lab06.dir/BSTList.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Lab06.dir/BSTList.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06/BSTList.c" -o CMakeFiles/Lab06.dir/BSTList.c.s

# Object files for target Lab06
Lab06_OBJECTS = \
"CMakeFiles/Lab06.dir/BSTList.c.o"

# External object files for target Lab06
Lab06_EXTERNAL_OBJECTS =

Lab06: CMakeFiles/Lab06.dir/BSTList.c.o
Lab06: CMakeFiles/Lab06.dir/build.make
Lab06: CMakeFiles/Lab06.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/student/Desktop/Anul 1/Sem 2/SD/Lab06/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Lab06"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab06.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab06.dir/build: Lab06

.PHONY : CMakeFiles/Lab06.dir/build

CMakeFiles/Lab06.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab06.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab06.dir/clean

CMakeFiles/Lab06.dir/depend:
	cd "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06" "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06" "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06/cmake-build-debug" "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06/cmake-build-debug" "/home/student/Desktop/Anul 1/Sem 2/SD/Lab06/cmake-build-debug/CMakeFiles/Lab06.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Lab06.dir/depend

