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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fuyajun/MyPlayground/my-program-wharehouse/c++/语言新特性研究

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fuyajun/MyPlayground/my-program-wharehouse/c++/build-语言新特性研究-Desktop-Default

# Include any dependencies generated for this target.
include CMakeFiles/init_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/init_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/init_test.dir/flags.make

CMakeFiles/init_test.dir/init_test.cpp.o: CMakeFiles/init_test.dir/flags.make
CMakeFiles/init_test.dir/init_test.cpp.o: /home/fuyajun/MyPlayground/my-program-wharehouse/c++/语言新特性研究/init_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fuyajun/MyPlayground/my-program-wharehouse/c++/build-语言新特性研究-Desktop-Default/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/init_test.dir/init_test.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/init_test.dir/init_test.cpp.o -c /home/fuyajun/MyPlayground/my-program-wharehouse/c++/语言新特性研究/init_test.cpp

CMakeFiles/init_test.dir/init_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/init_test.dir/init_test.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fuyajun/MyPlayground/my-program-wharehouse/c++/语言新特性研究/init_test.cpp > CMakeFiles/init_test.dir/init_test.cpp.i

CMakeFiles/init_test.dir/init_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/init_test.dir/init_test.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fuyajun/MyPlayground/my-program-wharehouse/c++/语言新特性研究/init_test.cpp -o CMakeFiles/init_test.dir/init_test.cpp.s

CMakeFiles/init_test.dir/init_test.cpp.o.requires:
.PHONY : CMakeFiles/init_test.dir/init_test.cpp.o.requires

CMakeFiles/init_test.dir/init_test.cpp.o.provides: CMakeFiles/init_test.dir/init_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/init_test.dir/build.make CMakeFiles/init_test.dir/init_test.cpp.o.provides.build
.PHONY : CMakeFiles/init_test.dir/init_test.cpp.o.provides

CMakeFiles/init_test.dir/init_test.cpp.o.provides.build: CMakeFiles/init_test.dir/init_test.cpp.o

# Object files for target init_test
init_test_OBJECTS = \
"CMakeFiles/init_test.dir/init_test.cpp.o"

# External object files for target init_test
init_test_EXTERNAL_OBJECTS =

init_test: CMakeFiles/init_test.dir/init_test.cpp.o
init_test: CMakeFiles/init_test.dir/build.make
init_test: CMakeFiles/init_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable init_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/init_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/init_test.dir/build: init_test
.PHONY : CMakeFiles/init_test.dir/build

CMakeFiles/init_test.dir/requires: CMakeFiles/init_test.dir/init_test.cpp.o.requires
.PHONY : CMakeFiles/init_test.dir/requires

CMakeFiles/init_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/init_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/init_test.dir/clean

CMakeFiles/init_test.dir/depend:
	cd /home/fuyajun/MyPlayground/my-program-wharehouse/c++/build-语言新特性研究-Desktop-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fuyajun/MyPlayground/my-program-wharehouse/c++/语言新特性研究 /home/fuyajun/MyPlayground/my-program-wharehouse/c++/语言新特性研究 /home/fuyajun/MyPlayground/my-program-wharehouse/c++/build-语言新特性研究-Desktop-Default /home/fuyajun/MyPlayground/my-program-wharehouse/c++/build-语言新特性研究-Desktop-Default /home/fuyajun/MyPlayground/my-program-wharehouse/c++/build-语言新特性研究-Desktop-Default/CMakeFiles/init_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/init_test.dir/depend

