# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\julka\Desktop\Studia\git\c++\Macierze

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\julka\Desktop\Studia\git\c++\Macierze\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Macierze.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Macierze.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Macierze.dir/flags.make

CMakeFiles/Macierze.dir/main.cpp.obj: CMakeFiles/Macierze.dir/flags.make
CMakeFiles/Macierze.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\julka\Desktop\Studia\git\c++\Macierze\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Macierze.dir/main.cpp.obj"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Macierze.dir\main.cpp.obj -c C:\Users\julka\Desktop\Studia\git\c++\Macierze\main.cpp

CMakeFiles/Macierze.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Macierze.dir/main.cpp.i"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\julka\Desktop\Studia\git\c++\Macierze\main.cpp > CMakeFiles\Macierze.dir\main.cpp.i

CMakeFiles/Macierze.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Macierze.dir/main.cpp.s"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\julka\Desktop\Studia\git\c++\Macierze\main.cpp -o CMakeFiles\Macierze.dir\main.cpp.s

# Object files for target Macierze
Macierze_OBJECTS = \
"CMakeFiles/Macierze.dir/main.cpp.obj"

# External object files for target Macierze
Macierze_EXTERNAL_OBJECTS =

Macierze.exe: CMakeFiles/Macierze.dir/main.cpp.obj
Macierze.exe: CMakeFiles/Macierze.dir/build.make
Macierze.exe: CMakeFiles/Macierze.dir/linklibs.rsp
Macierze.exe: CMakeFiles/Macierze.dir/objects1.rsp
Macierze.exe: CMakeFiles/Macierze.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\julka\Desktop\Studia\git\c++\Macierze\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Macierze.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Macierze.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Macierze.dir/build: Macierze.exe
.PHONY : CMakeFiles/Macierze.dir/build

CMakeFiles/Macierze.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Macierze.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Macierze.dir/clean

CMakeFiles/Macierze.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\julka\Desktop\Studia\git\c++\Macierze C:\Users\julka\Desktop\Studia\git\c++\Macierze C:\Users\julka\Desktop\Studia\git\c++\Macierze\cmake-build-debug C:\Users\julka\Desktop\Studia\git\c++\Macierze\cmake-build-debug C:\Users\julka\Desktop\Studia\git\c++\Macierze\cmake-build-debug\CMakeFiles\Macierze.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Macierze.dir/depend
