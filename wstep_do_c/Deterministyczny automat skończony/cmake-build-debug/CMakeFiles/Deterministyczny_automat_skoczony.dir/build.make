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
CMAKE_SOURCE_DIR = "C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Deterministyczny_automat_skoczony.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Deterministyczny_automat_skoczony.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Deterministyczny_automat_skoczony.dir/flags.make

CMakeFiles/Deterministyczny_automat_skoczony.dir/main.c.obj: CMakeFiles/Deterministyczny_automat_skoczony.dir/flags.make
CMakeFiles/Deterministyczny_automat_skoczony.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Deterministyczny_automat_skoczony.dir/main.c.obj"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Deterministyczny_automat_skoczony.dir\main.c.obj -c "C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony\main.c"

CMakeFiles/Deterministyczny_automat_skoczony.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Deterministyczny_automat_skoczony.dir/main.c.i"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony\main.c" > CMakeFiles\Deterministyczny_automat_skoczony.dir\main.c.i

CMakeFiles/Deterministyczny_automat_skoczony.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Deterministyczny_automat_skoczony.dir/main.c.s"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony\main.c" -o CMakeFiles\Deterministyczny_automat_skoczony.dir\main.c.s

# Object files for target Deterministyczny_automat_skoczony
Deterministyczny_automat_skoczony_OBJECTS = \
"CMakeFiles/Deterministyczny_automat_skoczony.dir/main.c.obj"

# External object files for target Deterministyczny_automat_skoczony
Deterministyczny_automat_skoczony_EXTERNAL_OBJECTS =

Deterministyczny_automat_skoczony.exe: CMakeFiles/Deterministyczny_automat_skoczony.dir/main.c.obj
Deterministyczny_automat_skoczony.exe: CMakeFiles/Deterministyczny_automat_skoczony.dir/build.make
Deterministyczny_automat_skoczony.exe: CMakeFiles/Deterministyczny_automat_skoczony.dir/linklibs.rsp
Deterministyczny_automat_skoczony.exe: CMakeFiles/Deterministyczny_automat_skoczony.dir/objects1.rsp
Deterministyczny_automat_skoczony.exe: CMakeFiles/Deterministyczny_automat_skoczony.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Deterministyczny_automat_skoczony.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Deterministyczny_automat_skoczony.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Deterministyczny_automat_skoczony.dir/build: Deterministyczny_automat_skoczony.exe
.PHONY : CMakeFiles/Deterministyczny_automat_skoczony.dir/build

CMakeFiles/Deterministyczny_automat_skoczony.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Deterministyczny_automat_skoczony.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Deterministyczny_automat_skoczony.dir/clean

CMakeFiles/Deterministyczny_automat_skoczony.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony" "C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony" "C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony\cmake-build-debug" "C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony\cmake-build-debug" "C:\Users\julka\Desktop\Studia\git\wstep_do_c\Deterministyczny automat skończony\cmake-build-debug\CMakeFiles\Deterministyczny_automat_skoczony.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Deterministyczny_automat_skoczony.dir/depend

