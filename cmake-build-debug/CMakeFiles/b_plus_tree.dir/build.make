# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /cygdrive/c/Users/ecidi/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/ecidi/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/d/CLionProjects/b-plus-tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/d/CLionProjects/b-plus-tree/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/b_plus_tree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/b_plus_tree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/b_plus_tree.dir/flags.make

CMakeFiles/b_plus_tree.dir/main.c.o: CMakeFiles/b_plus_tree.dir/flags.make
CMakeFiles/b_plus_tree.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/d/CLionProjects/b-plus-tree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/b_plus_tree.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/b_plus_tree.dir/main.c.o   -c /cygdrive/d/CLionProjects/b-plus-tree/main.c

CMakeFiles/b_plus_tree.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/b_plus_tree.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/d/CLionProjects/b-plus-tree/main.c > CMakeFiles/b_plus_tree.dir/main.c.i

CMakeFiles/b_plus_tree.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/b_plus_tree.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/d/CLionProjects/b-plus-tree/main.c -o CMakeFiles/b_plus_tree.dir/main.c.s

CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.o: CMakeFiles/b_plus_tree.dir/flags.make
CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.o: ../src/BPlusTree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/d/CLionProjects/b-plus-tree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.o   -c /cygdrive/d/CLionProjects/b-plus-tree/src/BPlusTree.c

CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/d/CLionProjects/b-plus-tree/src/BPlusTree.c > CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.i

CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/d/CLionProjects/b-plus-tree/src/BPlusTree.c -o CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.s

# Object files for target b_plus_tree
b_plus_tree_OBJECTS = \
"CMakeFiles/b_plus_tree.dir/main.c.o" \
"CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.o"

# External object files for target b_plus_tree
b_plus_tree_EXTERNAL_OBJECTS =

b_plus_tree.exe: CMakeFiles/b_plus_tree.dir/main.c.o
b_plus_tree.exe: CMakeFiles/b_plus_tree.dir/src/BPlusTree.c.o
b_plus_tree.exe: CMakeFiles/b_plus_tree.dir/build.make
b_plus_tree.exe: CMakeFiles/b_plus_tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/d/CLionProjects/b-plus-tree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable b_plus_tree.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/b_plus_tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/b_plus_tree.dir/build: b_plus_tree.exe

.PHONY : CMakeFiles/b_plus_tree.dir/build

CMakeFiles/b_plus_tree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/b_plus_tree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/b_plus_tree.dir/clean

CMakeFiles/b_plus_tree.dir/depend:
	cd /cygdrive/d/CLionProjects/b-plus-tree/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/d/CLionProjects/b-plus-tree /cygdrive/d/CLionProjects/b-plus-tree /cygdrive/d/CLionProjects/b-plus-tree/cmake-build-debug /cygdrive/d/CLionProjects/b-plus-tree/cmake-build-debug /cygdrive/d/CLionProjects/b-plus-tree/cmake-build-debug/CMakeFiles/b_plus_tree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/b_plus_tree.dir/depend

