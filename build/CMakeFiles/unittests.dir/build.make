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

# Utility rule file for unittests.

# Include the progress variables for this target.
include CMakeFiles/unittests.dir/progress.make

CMakeFiles/unittests:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/mnt/c/Users/Mokhairy/CLionProjects/zsim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Set CMake argument ZSIM_BUILD_UNITTESTS=ON to enable unittests"

unittests: CMakeFiles/unittests
unittests: CMakeFiles/unittests.dir/build.make

.PHONY : unittests

# Rule to build all files generated by this target.
CMakeFiles/unittests.dir/build: unittests

.PHONY : CMakeFiles/unittests.dir/build

CMakeFiles/unittests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/unittests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/unittests.dir/clean

CMakeFiles/unittests.dir/depend:
	cd /mnt/c/Users/Mokhairy/CLionProjects/zsim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Mokhairy/CLionProjects/zsim /mnt/c/Users/Mokhairy/CLionProjects/zsim /mnt/c/Users/Mokhairy/CLionProjects/zsim/build /mnt/c/Users/Mokhairy/CLionProjects/zsim/build /mnt/c/Users/Mokhairy/CLionProjects/zsim/build/CMakeFiles/unittests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/unittests.dir/depend

