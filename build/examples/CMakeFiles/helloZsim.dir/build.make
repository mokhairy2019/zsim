# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Mokhairy/CLionProjects/zsim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Mokhairy/CLionProjects/zsim/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/helloZsim.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/helloZsim.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/helloZsim.dir/flags.make

examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o: examples/CMakeFiles/helloZsim.dir/flags.make
examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o: ../examples/helloZsim.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Mokhairy/CLionProjects/zsim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o"
	cd /mnt/c/Users/Mokhairy/CLionProjects/zsim/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/helloZsim.dir/helloZsim.cpp.o -c /mnt/c/Users/Mokhairy/CLionProjects/zsim/examples/helloZsim.cpp

examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloZsim.dir/helloZsim.cpp.i"
	cd /mnt/c/Users/Mokhairy/CLionProjects/zsim/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Mokhairy/CLionProjects/zsim/examples/helloZsim.cpp > CMakeFiles/helloZsim.dir/helloZsim.cpp.i

examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloZsim.dir/helloZsim.cpp.s"
	cd /mnt/c/Users/Mokhairy/CLionProjects/zsim/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Mokhairy/CLionProjects/zsim/examples/helloZsim.cpp -o CMakeFiles/helloZsim.dir/helloZsim.cpp.s

examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o.requires:

.PHONY : examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o.requires

examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o.provides: examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/helloZsim.dir/build.make examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o.provides.build
.PHONY : examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o.provides

examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o.provides.build: examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o


# Object files for target helloZsim
helloZsim_OBJECTS = \
"CMakeFiles/helloZsim.dir/helloZsim.cpp.o"

# External object files for target helloZsim
helloZsim_EXTERNAL_OBJECTS =

bin/helloZsim: examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o
bin/helloZsim: examples/CMakeFiles/helloZsim.dir/build.make
bin/helloZsim: lib/libzsim.a
bin/helloZsim: examples/CMakeFiles/helloZsim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Mokhairy/CLionProjects/zsim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/helloZsim"
	cd /mnt/c/Users/Mokhairy/CLionProjects/zsim/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/helloZsim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/helloZsim.dir/build: bin/helloZsim

.PHONY : examples/CMakeFiles/helloZsim.dir/build

examples/CMakeFiles/helloZsim.dir/requires: examples/CMakeFiles/helloZsim.dir/helloZsim.cpp.o.requires

.PHONY : examples/CMakeFiles/helloZsim.dir/requires

examples/CMakeFiles/helloZsim.dir/clean:
	cd /mnt/c/Users/Mokhairy/CLionProjects/zsim/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/helloZsim.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/helloZsim.dir/clean

examples/CMakeFiles/helloZsim.dir/depend:
	cd /mnt/c/Users/Mokhairy/CLionProjects/zsim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Mokhairy/CLionProjects/zsim /mnt/c/Users/Mokhairy/CLionProjects/zsim/examples /mnt/c/Users/Mokhairy/CLionProjects/zsim/build /mnt/c/Users/Mokhairy/CLionProjects/zsim/build/examples /mnt/c/Users/Mokhairy/CLionProjects/zsim/build/examples/CMakeFiles/helloZsim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/helloZsim.dir/depend

