# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_COMMAND = /home/pelegs29/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/pelegs29/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pelegs29/Documents/ClionProjects/anomaly_detector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pelegs29/Documents/ClionProjects/anomaly_detector/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/anomaly_detector.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/anomaly_detector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/anomaly_detector.dir/flags.make

CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.o: CMakeFiles/anomaly_detector.dir/flags.make
CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.o: ../anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pelegs29/Documents/ClionProjects/anomaly_detector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.o -c /home/pelegs29/Documents/ClionProjects/anomaly_detector/anomaly_detection_util.cpp

CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pelegs29/Documents/ClionProjects/anomaly_detector/anomaly_detection_util.cpp > CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.i

CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pelegs29/Documents/ClionProjects/anomaly_detector/anomaly_detection_util.cpp -o CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.s

# Object files for target anomaly_detector
anomaly_detector_OBJECTS = \
"CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.o"

# External object files for target anomaly_detector
anomaly_detector_EXTERNAL_OBJECTS =

anomaly_detector: CMakeFiles/anomaly_detector.dir/anomaly_detection_util.cpp.o
anomaly_detector: CMakeFiles/anomaly_detector.dir/build.make
anomaly_detector: CMakeFiles/anomaly_detector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pelegs29/Documents/ClionProjects/anomaly_detector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable anomaly_detector"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/anomaly_detector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/anomaly_detector.dir/build: anomaly_detector
.PHONY : CMakeFiles/anomaly_detector.dir/build

CMakeFiles/anomaly_detector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/anomaly_detector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/anomaly_detector.dir/clean

CMakeFiles/anomaly_detector.dir/depend:
	cd /home/pelegs29/Documents/ClionProjects/anomaly_detector/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pelegs29/Documents/ClionProjects/anomaly_detector /home/pelegs29/Documents/ClionProjects/anomaly_detector /home/pelegs29/Documents/ClionProjects/anomaly_detector/cmake-build-debug /home/pelegs29/Documents/ClionProjects/anomaly_detector/cmake-build-debug /home/pelegs29/Documents/ClionProjects/anomaly_detector/cmake-build-debug/CMakeFiles/anomaly_detector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/anomaly_detector.dir/depend

