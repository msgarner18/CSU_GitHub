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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /s/bach/e/under/ms675199/CS253/hw1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /s/bach/e/under/ms675199/CS253/hw1

# Utility rule file for hw1.tar.

# Include the progress variables for this target.
include CMakeFiles/hw1.tar.dir/progress.make

CMakeFiles/hw1.tar:
	tar cf hw1.tar main.cc CMakeLists.txt

hw1.tar: CMakeFiles/hw1.tar
hw1.tar: CMakeFiles/hw1.tar.dir/build.make

.PHONY : hw1.tar

# Rule to build all files generated by this target.
CMakeFiles/hw1.tar.dir/build: hw1.tar

.PHONY : CMakeFiles/hw1.tar.dir/build

CMakeFiles/hw1.tar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw1.tar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw1.tar.dir/clean

CMakeFiles/hw1.tar.dir/depend:
	cd /s/bach/e/under/ms675199/CS253/hw1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /s/bach/e/under/ms675199/CS253/hw1 /s/bach/e/under/ms675199/CS253/hw1 /s/bach/e/under/ms675199/CS253/hw1 /s/bach/e/under/ms675199/CS253/hw1 /s/bach/e/under/ms675199/CS253/hw1/CMakeFiles/hw1.tar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw1.tar.dir/depend
