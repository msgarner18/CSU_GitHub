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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /s/bach/e/under/ms675199/CS253/hw5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /s/bach/e/under/ms675199/CS253/hw5

# Include any dependencies generated for this target.
include CMakeFiles/hw5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw5.dir/flags.make

CMakeFiles/hw5.dir/Enemy.cc.o: CMakeFiles/hw5.dir/flags.make
CMakeFiles/hw5.dir/Enemy.cc.o: Enemy.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/s/bach/e/under/ms675199/CS253/hw5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw5.dir/Enemy.cc.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw5.dir/Enemy.cc.o -c /s/bach/e/under/ms675199/CS253/hw5/Enemy.cc

CMakeFiles/hw5.dir/Enemy.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw5.dir/Enemy.cc.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /s/bach/e/under/ms675199/CS253/hw5/Enemy.cc > CMakeFiles/hw5.dir/Enemy.cc.i

CMakeFiles/hw5.dir/Enemy.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw5.dir/Enemy.cc.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /s/bach/e/under/ms675199/CS253/hw5/Enemy.cc -o CMakeFiles/hw5.dir/Enemy.cc.s

CMakeFiles/hw5.dir/Gallery.cc.o: CMakeFiles/hw5.dir/flags.make
CMakeFiles/hw5.dir/Gallery.cc.o: Gallery.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/s/bach/e/under/ms675199/CS253/hw5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hw5.dir/Gallery.cc.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw5.dir/Gallery.cc.o -c /s/bach/e/under/ms675199/CS253/hw5/Gallery.cc

CMakeFiles/hw5.dir/Gallery.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw5.dir/Gallery.cc.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /s/bach/e/under/ms675199/CS253/hw5/Gallery.cc > CMakeFiles/hw5.dir/Gallery.cc.i

CMakeFiles/hw5.dir/Gallery.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw5.dir/Gallery.cc.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /s/bach/e/under/ms675199/CS253/hw5/Gallery.cc -o CMakeFiles/hw5.dir/Gallery.cc.s

# Object files for target hw5
hw5_OBJECTS = \
"CMakeFiles/hw5.dir/Enemy.cc.o" \
"CMakeFiles/hw5.dir/Gallery.cc.o"

# External object files for target hw5
hw5_EXTERNAL_OBJECTS =

libhw5.a: CMakeFiles/hw5.dir/Enemy.cc.o
libhw5.a: CMakeFiles/hw5.dir/Gallery.cc.o
libhw5.a: CMakeFiles/hw5.dir/build.make
libhw5.a: CMakeFiles/hw5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/s/bach/e/under/ms675199/CS253/hw5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libhw5.a"
	$(CMAKE_COMMAND) -P CMakeFiles/hw5.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw5.dir/build: libhw5.a

.PHONY : CMakeFiles/hw5.dir/build

CMakeFiles/hw5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw5.dir/clean

CMakeFiles/hw5.dir/depend:
	cd /s/bach/e/under/ms675199/CS253/hw5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /s/bach/e/under/ms675199/CS253/hw5 /s/bach/e/under/ms675199/CS253/hw5 /s/bach/e/under/ms675199/CS253/hw5 /s/bach/e/under/ms675199/CS253/hw5 /s/bach/e/under/ms675199/CS253/hw5/CMakeFiles/hw5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw5.dir/depend

