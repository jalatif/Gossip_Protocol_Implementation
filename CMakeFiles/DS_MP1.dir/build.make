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
CMAKE_SOURCE_DIR = /home/manshu/Templates/EXEs/CS425/DS_MP1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/manshu/Templates/EXEs/CS425/DS_MP1

# Include any dependencies generated for this target.
include CMakeFiles/DS_MP1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DS_MP1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DS_MP1.dir/flags.make

CMakeFiles/DS_MP1.dir/mp1_node.c.o: CMakeFiles/DS_MP1.dir/flags.make
CMakeFiles/DS_MP1.dir/mp1_node.c.o: mp1_node.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/manshu/Templates/EXEs/CS425/DS_MP1/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/DS_MP1.dir/mp1_node.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/DS_MP1.dir/mp1_node.c.o   -c /home/manshu/Templates/EXEs/CS425/DS_MP1/mp1_node.c

CMakeFiles/DS_MP1.dir/mp1_node.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DS_MP1.dir/mp1_node.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/manshu/Templates/EXEs/CS425/DS_MP1/mp1_node.c > CMakeFiles/DS_MP1.dir/mp1_node.c.i

CMakeFiles/DS_MP1.dir/mp1_node.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DS_MP1.dir/mp1_node.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/manshu/Templates/EXEs/CS425/DS_MP1/mp1_node.c -o CMakeFiles/DS_MP1.dir/mp1_node.c.s

CMakeFiles/DS_MP1.dir/mp1_node.c.o.requires:
.PHONY : CMakeFiles/DS_MP1.dir/mp1_node.c.o.requires

CMakeFiles/DS_MP1.dir/mp1_node.c.o.provides: CMakeFiles/DS_MP1.dir/mp1_node.c.o.requires
	$(MAKE) -f CMakeFiles/DS_MP1.dir/build.make CMakeFiles/DS_MP1.dir/mp1_node.c.o.provides.build
.PHONY : CMakeFiles/DS_MP1.dir/mp1_node.c.o.provides

CMakeFiles/DS_MP1.dir/mp1_node.c.o.provides.build: CMakeFiles/DS_MP1.dir/mp1_node.c.o

CMakeFiles/DS_MP1.dir/emulnet.c.o: CMakeFiles/DS_MP1.dir/flags.make
CMakeFiles/DS_MP1.dir/emulnet.c.o: emulnet.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/manshu/Templates/EXEs/CS425/DS_MP1/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/DS_MP1.dir/emulnet.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/DS_MP1.dir/emulnet.c.o   -c /home/manshu/Templates/EXEs/CS425/DS_MP1/emulnet.c

CMakeFiles/DS_MP1.dir/emulnet.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DS_MP1.dir/emulnet.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/manshu/Templates/EXEs/CS425/DS_MP1/emulnet.c > CMakeFiles/DS_MP1.dir/emulnet.c.i

CMakeFiles/DS_MP1.dir/emulnet.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DS_MP1.dir/emulnet.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/manshu/Templates/EXEs/CS425/DS_MP1/emulnet.c -o CMakeFiles/DS_MP1.dir/emulnet.c.s

CMakeFiles/DS_MP1.dir/emulnet.c.o.requires:
.PHONY : CMakeFiles/DS_MP1.dir/emulnet.c.o.requires

CMakeFiles/DS_MP1.dir/emulnet.c.o.provides: CMakeFiles/DS_MP1.dir/emulnet.c.o.requires
	$(MAKE) -f CMakeFiles/DS_MP1.dir/build.make CMakeFiles/DS_MP1.dir/emulnet.c.o.provides.build
.PHONY : CMakeFiles/DS_MP1.dir/emulnet.c.o.provides

CMakeFiles/DS_MP1.dir/emulnet.c.o.provides.build: CMakeFiles/DS_MP1.dir/emulnet.c.o

CMakeFiles/DS_MP1.dir/app.c.o: CMakeFiles/DS_MP1.dir/flags.make
CMakeFiles/DS_MP1.dir/app.c.o: app.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/manshu/Templates/EXEs/CS425/DS_MP1/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/DS_MP1.dir/app.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/DS_MP1.dir/app.c.o   -c /home/manshu/Templates/EXEs/CS425/DS_MP1/app.c

CMakeFiles/DS_MP1.dir/app.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DS_MP1.dir/app.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/manshu/Templates/EXEs/CS425/DS_MP1/app.c > CMakeFiles/DS_MP1.dir/app.c.i

CMakeFiles/DS_MP1.dir/app.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DS_MP1.dir/app.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/manshu/Templates/EXEs/CS425/DS_MP1/app.c -o CMakeFiles/DS_MP1.dir/app.c.s

CMakeFiles/DS_MP1.dir/app.c.o.requires:
.PHONY : CMakeFiles/DS_MP1.dir/app.c.o.requires

CMakeFiles/DS_MP1.dir/app.c.o.provides: CMakeFiles/DS_MP1.dir/app.c.o.requires
	$(MAKE) -f CMakeFiles/DS_MP1.dir/build.make CMakeFiles/DS_MP1.dir/app.c.o.provides.build
.PHONY : CMakeFiles/DS_MP1.dir/app.c.o.provides

CMakeFiles/DS_MP1.dir/app.c.o.provides.build: CMakeFiles/DS_MP1.dir/app.c.o

CMakeFiles/DS_MP1.dir/log.c.o: CMakeFiles/DS_MP1.dir/flags.make
CMakeFiles/DS_MP1.dir/log.c.o: log.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/manshu/Templates/EXEs/CS425/DS_MP1/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/DS_MP1.dir/log.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/DS_MP1.dir/log.c.o   -c /home/manshu/Templates/EXEs/CS425/DS_MP1/log.c

CMakeFiles/DS_MP1.dir/log.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DS_MP1.dir/log.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/manshu/Templates/EXEs/CS425/DS_MP1/log.c > CMakeFiles/DS_MP1.dir/log.c.i

CMakeFiles/DS_MP1.dir/log.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DS_MP1.dir/log.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/manshu/Templates/EXEs/CS425/DS_MP1/log.c -o CMakeFiles/DS_MP1.dir/log.c.s

CMakeFiles/DS_MP1.dir/log.c.o.requires:
.PHONY : CMakeFiles/DS_MP1.dir/log.c.o.requires

CMakeFiles/DS_MP1.dir/log.c.o.provides: CMakeFiles/DS_MP1.dir/log.c.o.requires
	$(MAKE) -f CMakeFiles/DS_MP1.dir/build.make CMakeFiles/DS_MP1.dir/log.c.o.provides.build
.PHONY : CMakeFiles/DS_MP1.dir/log.c.o.provides

CMakeFiles/DS_MP1.dir/log.c.o.provides.build: CMakeFiles/DS_MP1.dir/log.c.o

CMakeFiles/DS_MP1.dir/params.c.o: CMakeFiles/DS_MP1.dir/flags.make
CMakeFiles/DS_MP1.dir/params.c.o: params.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/manshu/Templates/EXEs/CS425/DS_MP1/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/DS_MP1.dir/params.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/DS_MP1.dir/params.c.o   -c /home/manshu/Templates/EXEs/CS425/DS_MP1/params.c

CMakeFiles/DS_MP1.dir/params.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DS_MP1.dir/params.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/manshu/Templates/EXEs/CS425/DS_MP1/params.c > CMakeFiles/DS_MP1.dir/params.c.i

CMakeFiles/DS_MP1.dir/params.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DS_MP1.dir/params.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/manshu/Templates/EXEs/CS425/DS_MP1/params.c -o CMakeFiles/DS_MP1.dir/params.c.s

CMakeFiles/DS_MP1.dir/params.c.o.requires:
.PHONY : CMakeFiles/DS_MP1.dir/params.c.o.requires

CMakeFiles/DS_MP1.dir/params.c.o.provides: CMakeFiles/DS_MP1.dir/params.c.o.requires
	$(MAKE) -f CMakeFiles/DS_MP1.dir/build.make CMakeFiles/DS_MP1.dir/params.c.o.provides.build
.PHONY : CMakeFiles/DS_MP1.dir/params.c.o.provides

CMakeFiles/DS_MP1.dir/params.c.o.provides.build: CMakeFiles/DS_MP1.dir/params.c.o

CMakeFiles/DS_MP1.dir/queue.c.o: CMakeFiles/DS_MP1.dir/flags.make
CMakeFiles/DS_MP1.dir/queue.c.o: queue.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/manshu/Templates/EXEs/CS425/DS_MP1/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/DS_MP1.dir/queue.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/DS_MP1.dir/queue.c.o   -c /home/manshu/Templates/EXEs/CS425/DS_MP1/queue.c

CMakeFiles/DS_MP1.dir/queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DS_MP1.dir/queue.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/manshu/Templates/EXEs/CS425/DS_MP1/queue.c > CMakeFiles/DS_MP1.dir/queue.c.i

CMakeFiles/DS_MP1.dir/queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DS_MP1.dir/queue.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/manshu/Templates/EXEs/CS425/DS_MP1/queue.c -o CMakeFiles/DS_MP1.dir/queue.c.s

CMakeFiles/DS_MP1.dir/queue.c.o.requires:
.PHONY : CMakeFiles/DS_MP1.dir/queue.c.o.requires

CMakeFiles/DS_MP1.dir/queue.c.o.provides: CMakeFiles/DS_MP1.dir/queue.c.o.requires
	$(MAKE) -f CMakeFiles/DS_MP1.dir/build.make CMakeFiles/DS_MP1.dir/queue.c.o.provides.build
.PHONY : CMakeFiles/DS_MP1.dir/queue.c.o.provides

CMakeFiles/DS_MP1.dir/queue.c.o.provides.build: CMakeFiles/DS_MP1.dir/queue.c.o

# Object files for target DS_MP1
DS_MP1_OBJECTS = \
"CMakeFiles/DS_MP1.dir/mp1_node.c.o" \
"CMakeFiles/DS_MP1.dir/emulnet.c.o" \
"CMakeFiles/DS_MP1.dir/app.c.o" \
"CMakeFiles/DS_MP1.dir/log.c.o" \
"CMakeFiles/DS_MP1.dir/params.c.o" \
"CMakeFiles/DS_MP1.dir/queue.c.o"

# External object files for target DS_MP1
DS_MP1_EXTERNAL_OBJECTS =

DS_MP1: CMakeFiles/DS_MP1.dir/mp1_node.c.o
DS_MP1: CMakeFiles/DS_MP1.dir/emulnet.c.o
DS_MP1: CMakeFiles/DS_MP1.dir/app.c.o
DS_MP1: CMakeFiles/DS_MP1.dir/log.c.o
DS_MP1: CMakeFiles/DS_MP1.dir/params.c.o
DS_MP1: CMakeFiles/DS_MP1.dir/queue.c.o
DS_MP1: CMakeFiles/DS_MP1.dir/build.make
DS_MP1: CMakeFiles/DS_MP1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable DS_MP1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DS_MP1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DS_MP1.dir/build: DS_MP1
.PHONY : CMakeFiles/DS_MP1.dir/build

CMakeFiles/DS_MP1.dir/requires: CMakeFiles/DS_MP1.dir/mp1_node.c.o.requires
CMakeFiles/DS_MP1.dir/requires: CMakeFiles/DS_MP1.dir/emulnet.c.o.requires
CMakeFiles/DS_MP1.dir/requires: CMakeFiles/DS_MP1.dir/app.c.o.requires
CMakeFiles/DS_MP1.dir/requires: CMakeFiles/DS_MP1.dir/log.c.o.requires
CMakeFiles/DS_MP1.dir/requires: CMakeFiles/DS_MP1.dir/params.c.o.requires
CMakeFiles/DS_MP1.dir/requires: CMakeFiles/DS_MP1.dir/queue.c.o.requires
.PHONY : CMakeFiles/DS_MP1.dir/requires

CMakeFiles/DS_MP1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DS_MP1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DS_MP1.dir/clean

CMakeFiles/DS_MP1.dir/depend:
	cd /home/manshu/Templates/EXEs/CS425/DS_MP1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/manshu/Templates/EXEs/CS425/DS_MP1 /home/manshu/Templates/EXEs/CS425/DS_MP1 /home/manshu/Templates/EXEs/CS425/DS_MP1 /home/manshu/Templates/EXEs/CS425/DS_MP1 /home/manshu/Templates/EXEs/CS425/DS_MP1/CMakeFiles/DS_MP1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DS_MP1.dir/depend

