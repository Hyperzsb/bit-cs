# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/part_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/part_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/part_1.dir/flags.make

CMakeFiles/part_1.dir/main.cpp.obj: CMakeFiles/part_1.dir/flags.make
CMakeFiles/part_1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/part_1.dir/main.cpp.obj"
	"D:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\part_1.dir\main.cpp.obj -c "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\main.cpp"

CMakeFiles/part_1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/part_1.dir/main.cpp.i"
	"D:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\main.cpp" > CMakeFiles\part_1.dir\main.cpp.i

CMakeFiles/part_1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/part_1.dir/main.cpp.s"
	"D:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\main.cpp" -o CMakeFiles\part_1.dir\main.cpp.s

CMakeFiles/part_1.dir/array.cpp.obj: CMakeFiles/part_1.dir/flags.make
CMakeFiles/part_1.dir/array.cpp.obj: ../array.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/part_1.dir/array.cpp.obj"
	"D:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\part_1.dir\array.cpp.obj -c "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\array.cpp"

CMakeFiles/part_1.dir/array.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/part_1.dir/array.cpp.i"
	"D:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\array.cpp" > CMakeFiles\part_1.dir\array.cpp.i

CMakeFiles/part_1.dir/array.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/part_1.dir/array.cpp.s"
	"D:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\array.cpp" -o CMakeFiles\part_1.dir\array.cpp.s

# Object files for target part_1
part_1_OBJECTS = \
"CMakeFiles/part_1.dir/main.cpp.obj" \
"CMakeFiles/part_1.dir/array.cpp.obj"

# External object files for target part_1
part_1_EXTERNAL_OBJECTS =

part_1.exe: CMakeFiles/part_1.dir/main.cpp.obj
part_1.exe: CMakeFiles/part_1.dir/array.cpp.obj
part_1.exe: CMakeFiles/part_1.dir/build.make
part_1.exe: CMakeFiles/part_1.dir/linklibs.rsp
part_1.exe: CMakeFiles/part_1.dir/objects1.rsp
part_1.exe: CMakeFiles/part_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable part_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\part_1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/part_1.dir/build: part_1.exe

.PHONY : CMakeFiles/part_1.dir/build

CMakeFiles/part_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\part_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/part_1.dir/clean

CMakeFiles/part_1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1" "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1" "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\cmake-build-debug" "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\cmake-build-debug" "E:\Private Files\BIT\2020\object-oriented-technology-and-methods\exp-7\part-1\cmake-build-debug\CMakeFiles\part_1.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/part_1.dir/depend

