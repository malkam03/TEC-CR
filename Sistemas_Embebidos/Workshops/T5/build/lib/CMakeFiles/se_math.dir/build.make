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
CMAKE_SOURCE_DIR = /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/se_math.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/se_math.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/se_math.dir/flags.make

lib/CMakeFiles/se_math.dir/libse_math.c.o: lib/CMakeFiles/se_math.dir/flags.make
lib/CMakeFiles/se_math.dir/libse_math.c.o: ../lib/libse_math.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/CMakeFiles/se_math.dir/libse_math.c.o"
	cd /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/se_math.dir/libse_math.c.o   -c /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/lib/libse_math.c

lib/CMakeFiles/se_math.dir/libse_math.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/se_math.dir/libse_math.c.i"
	cd /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/lib/libse_math.c > CMakeFiles/se_math.dir/libse_math.c.i

lib/CMakeFiles/se_math.dir/libse_math.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/se_math.dir/libse_math.c.s"
	cd /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/lib/libse_math.c -o CMakeFiles/se_math.dir/libse_math.c.s

lib/CMakeFiles/se_math.dir/libse_math.c.o.requires:

.PHONY : lib/CMakeFiles/se_math.dir/libse_math.c.o.requires

lib/CMakeFiles/se_math.dir/libse_math.c.o.provides: lib/CMakeFiles/se_math.dir/libse_math.c.o.requires
	$(MAKE) -f lib/CMakeFiles/se_math.dir/build.make lib/CMakeFiles/se_math.dir/libse_math.c.o.provides.build
.PHONY : lib/CMakeFiles/se_math.dir/libse_math.c.o.provides

lib/CMakeFiles/se_math.dir/libse_math.c.o.provides.build: lib/CMakeFiles/se_math.dir/libse_math.c.o


# Object files for target se_math
se_math_OBJECTS = \
"CMakeFiles/se_math.dir/libse_math.c.o"

# External object files for target se_math
se_math_EXTERNAL_OBJECTS =

lib/libse_math.so: lib/CMakeFiles/se_math.dir/libse_math.c.o
lib/libse_math.so: lib/CMakeFiles/se_math.dir/build.make
lib/libse_math.so: lib/CMakeFiles/se_math.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libse_math.so"
	cd /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/se_math.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/se_math.dir/build: lib/libse_math.so

.PHONY : lib/CMakeFiles/se_math.dir/build

lib/CMakeFiles/se_math.dir/requires: lib/CMakeFiles/se_math.dir/libse_math.c.o.requires

.PHONY : lib/CMakeFiles/se_math.dir/requires

lib/CMakeFiles/se_math.dir/clean:
	cd /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/se_math.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/se_math.dir/clean

lib/CMakeFiles/se_math.dir/depend:
	cd /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5 /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/lib /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build/lib /home/malkam03/Documents/TEC-CR/Sistemas_Embebidos/Workshops/T5/build/lib/CMakeFiles/se_math.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/se_math.dir/depend

