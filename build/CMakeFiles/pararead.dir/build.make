# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/kang/dev/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kang/dev/test/build

# Include any dependencies generated for this target.
include CMakeFiles/pararead.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pararead.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pararead.dir/flags.make

CMakeFiles/pararead.dir/pararead.cpp.o: CMakeFiles/pararead.dir/flags.make
CMakeFiles/pararead.dir/pararead.cpp.o: ../pararead.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kang/dev/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pararead.dir/pararead.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pararead.dir/pararead.cpp.o -c /home/kang/dev/test/pararead.cpp

CMakeFiles/pararead.dir/pararead.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pararead.dir/pararead.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kang/dev/test/pararead.cpp > CMakeFiles/pararead.dir/pararead.cpp.i

CMakeFiles/pararead.dir/pararead.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pararead.dir/pararead.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kang/dev/test/pararead.cpp -o CMakeFiles/pararead.dir/pararead.cpp.s

CMakeFiles/pararead.dir/pararead.cpp.o.requires:

.PHONY : CMakeFiles/pararead.dir/pararead.cpp.o.requires

CMakeFiles/pararead.dir/pararead.cpp.o.provides: CMakeFiles/pararead.dir/pararead.cpp.o.requires
	$(MAKE) -f CMakeFiles/pararead.dir/build.make CMakeFiles/pararead.dir/pararead.cpp.o.provides.build
.PHONY : CMakeFiles/pararead.dir/pararead.cpp.o.provides

CMakeFiles/pararead.dir/pararead.cpp.o.provides.build: CMakeFiles/pararead.dir/pararead.cpp.o


# Object files for target pararead
pararead_OBJECTS = \
"CMakeFiles/pararead.dir/pararead.cpp.o"

# External object files for target pararead
pararead_EXTERNAL_OBJECTS =

pararead: CMakeFiles/pararead.dir/pararead.cpp.o
pararead: CMakeFiles/pararead.dir/build.make
pararead: CMakeFiles/pararead.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kang/dev/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pararead"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pararead.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pararead.dir/build: pararead

.PHONY : CMakeFiles/pararead.dir/build

CMakeFiles/pararead.dir/requires: CMakeFiles/pararead.dir/pararead.cpp.o.requires

.PHONY : CMakeFiles/pararead.dir/requires

CMakeFiles/pararead.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pararead.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pararead.dir/clean

CMakeFiles/pararead.dir/depend:
	cd /home/kang/dev/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kang/dev/test /home/kang/dev/test /home/kang/dev/test/build /home/kang/dev/test/build /home/kang/dev/test/build/CMakeFiles/pararead.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pararead.dir/depend

