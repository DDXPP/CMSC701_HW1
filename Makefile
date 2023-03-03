# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/elliot/CMSC701_HW1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/elliot/CMSC701_HW1

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.25.2/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.25.2/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/elliot/CMSC701_HW1/CMakeFiles /Users/elliot/CMSC701_HW1//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/elliot/CMSC701_HW1/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named sais

# Build rule for target.
sais: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 sais
.PHONY : sais

# fast build rule for target.
sais/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sais.dir/build.make CMakeFiles/sais.dir/build
.PHONY : sais/fast

#=============================================================================
# Target rules for targets named buildsa

# Build rule for target.
buildsa: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 buildsa
.PHONY : buildsa

# fast build rule for target.
buildsa/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/buildsa.dir/build.make CMakeFiles/buildsa.dir/build
.PHONY : buildsa/fast

#=============================================================================
# Target rules for targets named querysa

# Build rule for target.
querysa: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 querysa
.PHONY : querysa

# fast build rule for target.
querysa/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/querysa.dir/build.make CMakeFiles/querysa.dir/build
.PHONY : querysa/fast

src/buildsa.o: src/buildsa.cpp.o
.PHONY : src/buildsa.o

# target to build an object file
src/buildsa.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/buildsa.dir/build.make CMakeFiles/buildsa.dir/src/buildsa.cpp.o
.PHONY : src/buildsa.cpp.o

src/buildsa.i: src/buildsa.cpp.i
.PHONY : src/buildsa.i

# target to preprocess a source file
src/buildsa.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/buildsa.dir/build.make CMakeFiles/buildsa.dir/src/buildsa.cpp.i
.PHONY : src/buildsa.cpp.i

src/buildsa.s: src/buildsa.cpp.s
.PHONY : src/buildsa.s

# target to generate assembly for a file
src/buildsa.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/buildsa.dir/build.make CMakeFiles/buildsa.dir/src/buildsa.cpp.s
.PHONY : src/buildsa.cpp.s

src/libsais.o: src/libsais.c.o
.PHONY : src/libsais.o

# target to build an object file
src/libsais.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sais.dir/build.make CMakeFiles/sais.dir/src/libsais.c.o
.PHONY : src/libsais.c.o

src/libsais.i: src/libsais.c.i
.PHONY : src/libsais.i

# target to preprocess a source file
src/libsais.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sais.dir/build.make CMakeFiles/sais.dir/src/libsais.c.i
.PHONY : src/libsais.c.i

src/libsais.s: src/libsais.c.s
.PHONY : src/libsais.s

# target to generate assembly for a file
src/libsais.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sais.dir/build.make CMakeFiles/sais.dir/src/libsais.c.s
.PHONY : src/libsais.c.s

src/libsais64.o: src/libsais64.c.o
.PHONY : src/libsais64.o

# target to build an object file
src/libsais64.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sais.dir/build.make CMakeFiles/sais.dir/src/libsais64.c.o
.PHONY : src/libsais64.c.o

src/libsais64.i: src/libsais64.c.i
.PHONY : src/libsais64.i

# target to preprocess a source file
src/libsais64.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sais.dir/build.make CMakeFiles/sais.dir/src/libsais64.c.i
.PHONY : src/libsais64.c.i

src/libsais64.s: src/libsais64.c.s
.PHONY : src/libsais64.s

# target to generate assembly for a file
src/libsais64.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sais.dir/build.make CMakeFiles/sais.dir/src/libsais64.c.s
.PHONY : src/libsais64.c.s

src/querysa.o: src/querysa.cpp.o
.PHONY : src/querysa.o

# target to build an object file
src/querysa.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/querysa.dir/build.make CMakeFiles/querysa.dir/src/querysa.cpp.o
.PHONY : src/querysa.cpp.o

src/querysa.i: src/querysa.cpp.i
.PHONY : src/querysa.i

# target to preprocess a source file
src/querysa.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/querysa.dir/build.make CMakeFiles/querysa.dir/src/querysa.cpp.i
.PHONY : src/querysa.cpp.i

src/querysa.s: src/querysa.cpp.s
.PHONY : src/querysa.s

# target to generate assembly for a file
src/querysa.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/querysa.dir/build.make CMakeFiles/querysa.dir/src/querysa.cpp.s
.PHONY : src/querysa.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... buildsa"
	@echo "... querysa"
	@echo "... sais"
	@echo "... src/buildsa.o"
	@echo "... src/buildsa.i"
	@echo "... src/buildsa.s"
	@echo "... src/libsais.o"
	@echo "... src/libsais.i"
	@echo "... src/libsais.s"
	@echo "... src/libsais64.o"
	@echo "... src/libsais64.i"
	@echo "... src/libsais64.s"
	@echo "... src/querysa.o"
	@echo "... src/querysa.i"
	@echo "... src/querysa.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

