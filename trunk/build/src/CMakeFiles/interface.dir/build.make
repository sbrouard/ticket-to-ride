# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build

# Include any dependencies generated for this target.
include src/CMakeFiles/interface.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/interface.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/interface.dir/flags.make

src/CMakeFiles/interface.dir/interface.c.o: src/CMakeFiles/interface.dir/flags.make
src/CMakeFiles/interface.dir/interface.c.o: ../src/interface.c
	$(CMAKE_COMMAND) -E cmake_progress_report /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/interface.dir/interface.c.o"
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/interface.dir/interface.c.o   -c /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/src/interface.c

src/CMakeFiles/interface.dir/interface.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/interface.dir/interface.c.i"
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/src/interface.c > CMakeFiles/interface.dir/interface.c.i

src/CMakeFiles/interface.dir/interface.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/interface.dir/interface.c.s"
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/src/interface.c -o CMakeFiles/interface.dir/interface.c.s

src/CMakeFiles/interface.dir/interface.c.o.requires:
.PHONY : src/CMakeFiles/interface.dir/interface.c.o.requires

src/CMakeFiles/interface.dir/interface.c.o.provides: src/CMakeFiles/interface.dir/interface.c.o.requires
	$(MAKE) -f src/CMakeFiles/interface.dir/build.make src/CMakeFiles/interface.dir/interface.c.o.provides.build
.PHONY : src/CMakeFiles/interface.dir/interface.c.o.provides

src/CMakeFiles/interface.dir/interface.c.o.provides.build: src/CMakeFiles/interface.dir/interface.c.o

# Object files for target interface
interface_OBJECTS = \
"CMakeFiles/interface.dir/interface.c.o"

# External object files for target interface
interface_EXTERNAL_OBJECTS =

src/libinterface.a: src/CMakeFiles/interface.dir/interface.c.o
src/libinterface.a: src/CMakeFiles/interface.dir/build.make
src/libinterface.a: src/CMakeFiles/interface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libinterface.a"
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/src && $(CMAKE_COMMAND) -P CMakeFiles/interface.dir/cmake_clean_target.cmake
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interface.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/interface.dir/build: src/libinterface.a
.PHONY : src/CMakeFiles/interface.dir/build

src/CMakeFiles/interface.dir/requires: src/CMakeFiles/interface.dir/interface.c.o.requires
.PHONY : src/CMakeFiles/interface.dir/requires

src/CMakeFiles/interface.dir/clean:
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/src && $(CMAKE_COMMAND) -P CMakeFiles/interface.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/interface.dir/clean

src/CMakeFiles/interface.dir/depend:
	cd /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/src /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/src /net/malt/i/sbrouard/Documents/projets6/s6-rails-1992/trunk/build/src/CMakeFiles/interface.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/interface.dir/depend

