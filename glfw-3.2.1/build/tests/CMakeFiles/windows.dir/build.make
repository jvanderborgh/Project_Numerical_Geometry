# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/windows.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/windows.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/windows.dir/flags.make

tests/CMakeFiles/windows.dir/windows.c.o: tests/CMakeFiles/windows.dir/flags.make
tests/CMakeFiles/windows.dir/windows.c.o: ../tests/windows.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/windows.dir/windows.c.o"
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/windows.dir/windows.c.o   -c /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/tests/windows.c

tests/CMakeFiles/windows.dir/windows.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/windows.dir/windows.c.i"
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/tests/windows.c > CMakeFiles/windows.dir/windows.c.i

tests/CMakeFiles/windows.dir/windows.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/windows.dir/windows.c.s"
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/tests/windows.c -o CMakeFiles/windows.dir/windows.c.s

tests/CMakeFiles/windows.dir/windows.c.o.requires:

.PHONY : tests/CMakeFiles/windows.dir/windows.c.o.requires

tests/CMakeFiles/windows.dir/windows.c.o.provides: tests/CMakeFiles/windows.dir/windows.c.o.requires
	$(MAKE) -f tests/CMakeFiles/windows.dir/build.make tests/CMakeFiles/windows.dir/windows.c.o.provides.build
.PHONY : tests/CMakeFiles/windows.dir/windows.c.o.provides

tests/CMakeFiles/windows.dir/windows.c.o.provides.build: tests/CMakeFiles/windows.dir/windows.c.o


tests/CMakeFiles/windows.dir/__/deps/getopt.c.o: tests/CMakeFiles/windows.dir/flags.make
tests/CMakeFiles/windows.dir/__/deps/getopt.c.o: ../deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/windows.dir/__/deps/getopt.c.o"
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/windows.dir/__/deps/getopt.c.o   -c /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/deps/getopt.c

tests/CMakeFiles/windows.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/windows.dir/__/deps/getopt.c.i"
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/deps/getopt.c > CMakeFiles/windows.dir/__/deps/getopt.c.i

tests/CMakeFiles/windows.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/windows.dir/__/deps/getopt.c.s"
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/deps/getopt.c -o CMakeFiles/windows.dir/__/deps/getopt.c.s

tests/CMakeFiles/windows.dir/__/deps/getopt.c.o.requires:

.PHONY : tests/CMakeFiles/windows.dir/__/deps/getopt.c.o.requires

tests/CMakeFiles/windows.dir/__/deps/getopt.c.o.provides: tests/CMakeFiles/windows.dir/__/deps/getopt.c.o.requires
	$(MAKE) -f tests/CMakeFiles/windows.dir/build.make tests/CMakeFiles/windows.dir/__/deps/getopt.c.o.provides.build
.PHONY : tests/CMakeFiles/windows.dir/__/deps/getopt.c.o.provides

tests/CMakeFiles/windows.dir/__/deps/getopt.c.o.provides.build: tests/CMakeFiles/windows.dir/__/deps/getopt.c.o


tests/CMakeFiles/windows.dir/__/deps/glad.c.o: tests/CMakeFiles/windows.dir/flags.make
tests/CMakeFiles/windows.dir/__/deps/glad.c.o: ../deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tests/CMakeFiles/windows.dir/__/deps/glad.c.o"
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/windows.dir/__/deps/glad.c.o   -c /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/deps/glad.c

tests/CMakeFiles/windows.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/windows.dir/__/deps/glad.c.i"
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/deps/glad.c > CMakeFiles/windows.dir/__/deps/glad.c.i

tests/CMakeFiles/windows.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/windows.dir/__/deps/glad.c.s"
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/deps/glad.c -o CMakeFiles/windows.dir/__/deps/glad.c.s

tests/CMakeFiles/windows.dir/__/deps/glad.c.o.requires:

.PHONY : tests/CMakeFiles/windows.dir/__/deps/glad.c.o.requires

tests/CMakeFiles/windows.dir/__/deps/glad.c.o.provides: tests/CMakeFiles/windows.dir/__/deps/glad.c.o.requires
	$(MAKE) -f tests/CMakeFiles/windows.dir/build.make tests/CMakeFiles/windows.dir/__/deps/glad.c.o.provides.build
.PHONY : tests/CMakeFiles/windows.dir/__/deps/glad.c.o.provides

tests/CMakeFiles/windows.dir/__/deps/glad.c.o.provides.build: tests/CMakeFiles/windows.dir/__/deps/glad.c.o


# Object files for target windows
windows_OBJECTS = \
"CMakeFiles/windows.dir/windows.c.o" \
"CMakeFiles/windows.dir/__/deps/getopt.c.o" \
"CMakeFiles/windows.dir/__/deps/glad.c.o"

# External object files for target windows
windows_EXTERNAL_OBJECTS =

tests/windows.app/Contents/MacOS/windows: tests/CMakeFiles/windows.dir/windows.c.o
tests/windows.app/Contents/MacOS/windows: tests/CMakeFiles/windows.dir/__/deps/getopt.c.o
tests/windows.app/Contents/MacOS/windows: tests/CMakeFiles/windows.dir/__/deps/glad.c.o
tests/windows.app/Contents/MacOS/windows: tests/CMakeFiles/windows.dir/build.make
tests/windows.app/Contents/MacOS/windows: src/libglfw3.a
tests/windows.app/Contents/MacOS/windows: tests/CMakeFiles/windows.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable windows.app/Contents/MacOS/windows"
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/windows.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/windows.dir/build: tests/windows.app/Contents/MacOS/windows

.PHONY : tests/CMakeFiles/windows.dir/build

tests/CMakeFiles/windows.dir/requires: tests/CMakeFiles/windows.dir/windows.c.o.requires
tests/CMakeFiles/windows.dir/requires: tests/CMakeFiles/windows.dir/__/deps/getopt.c.o.requires
tests/CMakeFiles/windows.dir/requires: tests/CMakeFiles/windows.dir/__/deps/glad.c.o.requires

.PHONY : tests/CMakeFiles/windows.dir/requires

tests/CMakeFiles/windows.dir/clean:
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/windows.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/windows.dir/clean

tests/CMakeFiles/windows.dir/depend:
	cd /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1 /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/tests /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/tests/CMakeFiles/windows.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/windows.dir/depend

