# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_SOURCE_DIR = /home/goluckyryan/Dropbox/programmings/Geant4/N04

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/goluckyryan/Dropbox/programmings/Geant4/N04-build

# Utility rule file for n4.

# Include the progress variables for this target.
include CMakeFiles/n4.dir/progress.make

CMakeFiles/n4: n04


n4: CMakeFiles/n4
n4: CMakeFiles/n4.dir/build.make

.PHONY : n4

# Rule to build all files generated by this target.
CMakeFiles/n4.dir/build: n4

.PHONY : CMakeFiles/n4.dir/build

CMakeFiles/n4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/n4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/n4.dir/clean

CMakeFiles/n4.dir/depend:
	cd /home/goluckyryan/Dropbox/programmings/Geant4/N04-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/goluckyryan/Dropbox/programmings/Geant4/N04 /home/goluckyryan/Dropbox/programmings/Geant4/N04 /home/goluckyryan/Dropbox/programmings/Geant4/N04-build /home/goluckyryan/Dropbox/programmings/Geant4/N04-build /home/goluckyryan/Dropbox/programmings/Geant4/N04-build/CMakeFiles/n4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/n4.dir/depend
