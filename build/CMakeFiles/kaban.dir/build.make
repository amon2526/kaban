# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Ivan\source\code\kaban

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Ivan\source\code\kaban\build

# Include any dependencies generated for this target.
include CMakeFiles/kaban.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/kaban.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/kaban.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kaban.dir/flags.make

CMakeFiles/kaban.dir/codegen:
.PHONY : CMakeFiles/kaban.dir/codegen

CMakeFiles/kaban.dir/src/main.cpp.obj: CMakeFiles/kaban.dir/flags.make
CMakeFiles/kaban.dir/src/main.cpp.obj: CMakeFiles/kaban.dir/includes_CXX.rsp
CMakeFiles/kaban.dir/src/main.cpp.obj: C:/Users/Ivan/source/code/kaban/src/main.cpp
CMakeFiles/kaban.dir/src/main.cpp.obj: CMakeFiles/kaban.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Ivan\source\code\kaban\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/kaban.dir/src/main.cpp.obj"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/kaban.dir/src/main.cpp.obj -MF CMakeFiles\kaban.dir\src\main.cpp.obj.d -o CMakeFiles\kaban.dir\src\main.cpp.obj -c C:\Users\Ivan\source\code\kaban\src\main.cpp

CMakeFiles/kaban.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/kaban.dir/src/main.cpp.i"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ivan\source\code\kaban\src\main.cpp > CMakeFiles\kaban.dir\src\main.cpp.i

CMakeFiles/kaban.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/kaban.dir/src/main.cpp.s"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ivan\source\code\kaban\src\main.cpp -o CMakeFiles\kaban.dir\src\main.cpp.s

CMakeFiles/kaban.dir/src/renderer.cpp.obj: CMakeFiles/kaban.dir/flags.make
CMakeFiles/kaban.dir/src/renderer.cpp.obj: CMakeFiles/kaban.dir/includes_CXX.rsp
CMakeFiles/kaban.dir/src/renderer.cpp.obj: C:/Users/Ivan/source/code/kaban/src/renderer.cpp
CMakeFiles/kaban.dir/src/renderer.cpp.obj: CMakeFiles/kaban.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Ivan\source\code\kaban\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/kaban.dir/src/renderer.cpp.obj"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/kaban.dir/src/renderer.cpp.obj -MF CMakeFiles\kaban.dir\src\renderer.cpp.obj.d -o CMakeFiles\kaban.dir\src\renderer.cpp.obj -c C:\Users\Ivan\source\code\kaban\src\renderer.cpp

CMakeFiles/kaban.dir/src/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/kaban.dir/src/renderer.cpp.i"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ivan\source\code\kaban\src\renderer.cpp > CMakeFiles\kaban.dir\src\renderer.cpp.i

CMakeFiles/kaban.dir/src/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/kaban.dir/src/renderer.cpp.s"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ivan\source\code\kaban\src\renderer.cpp -o CMakeFiles\kaban.dir\src\renderer.cpp.s

CMakeFiles/kaban.dir/src/game.cpp.obj: CMakeFiles/kaban.dir/flags.make
CMakeFiles/kaban.dir/src/game.cpp.obj: CMakeFiles/kaban.dir/includes_CXX.rsp
CMakeFiles/kaban.dir/src/game.cpp.obj: C:/Users/Ivan/source/code/kaban/src/game.cpp
CMakeFiles/kaban.dir/src/game.cpp.obj: CMakeFiles/kaban.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Ivan\source\code\kaban\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/kaban.dir/src/game.cpp.obj"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/kaban.dir/src/game.cpp.obj -MF CMakeFiles\kaban.dir\src\game.cpp.obj.d -o CMakeFiles\kaban.dir\src\game.cpp.obj -c C:\Users\Ivan\source\code\kaban\src\game.cpp

CMakeFiles/kaban.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/kaban.dir/src/game.cpp.i"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ivan\source\code\kaban\src\game.cpp > CMakeFiles\kaban.dir\src\game.cpp.i

CMakeFiles/kaban.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/kaban.dir/src/game.cpp.s"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ivan\source\code\kaban\src\game.cpp -o CMakeFiles\kaban.dir\src\game.cpp.s

CMakeFiles/kaban.dir/src/board.cpp.obj: CMakeFiles/kaban.dir/flags.make
CMakeFiles/kaban.dir/src/board.cpp.obj: CMakeFiles/kaban.dir/includes_CXX.rsp
CMakeFiles/kaban.dir/src/board.cpp.obj: C:/Users/Ivan/source/code/kaban/src/board.cpp
CMakeFiles/kaban.dir/src/board.cpp.obj: CMakeFiles/kaban.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Ivan\source\code\kaban\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/kaban.dir/src/board.cpp.obj"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/kaban.dir/src/board.cpp.obj -MF CMakeFiles\kaban.dir\src\board.cpp.obj.d -o CMakeFiles\kaban.dir\src\board.cpp.obj -c C:\Users\Ivan\source\code\kaban\src\board.cpp

CMakeFiles/kaban.dir/src/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/kaban.dir/src/board.cpp.i"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ivan\source\code\kaban\src\board.cpp > CMakeFiles\kaban.dir\src\board.cpp.i

CMakeFiles/kaban.dir/src/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/kaban.dir/src/board.cpp.s"
	C:\Programs\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ivan\source\code\kaban\src\board.cpp -o CMakeFiles\kaban.dir\src\board.cpp.s

# Object files for target kaban
kaban_OBJECTS = \
"CMakeFiles/kaban.dir/src/main.cpp.obj" \
"CMakeFiles/kaban.dir/src/renderer.cpp.obj" \
"CMakeFiles/kaban.dir/src/game.cpp.obj" \
"CMakeFiles/kaban.dir/src/board.cpp.obj"

# External object files for target kaban
kaban_EXTERNAL_OBJECTS =

kaban.exe: CMakeFiles/kaban.dir/src/main.cpp.obj
kaban.exe: CMakeFiles/kaban.dir/src/renderer.cpp.obj
kaban.exe: CMakeFiles/kaban.dir/src/game.cpp.obj
kaban.exe: CMakeFiles/kaban.dir/src/board.cpp.obj
kaban.exe: CMakeFiles/kaban.dir/build.make
kaban.exe: D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/debug/lib/libglfw3.a
kaban.exe: D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/debug/lib/libimguid.a
kaban.exe: D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/debug/lib/libgtest.a
kaban.exe: D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/debug/lib/libglfw3.a
kaban.exe: CMakeFiles/kaban.dir/linkLibs.rsp
kaban.exe: CMakeFiles/kaban.dir/objects1.rsp
kaban.exe: CMakeFiles/kaban.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Ivan\source\code\kaban\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable kaban.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\kaban.dir\link.txt --verbose=$(VERBOSE)
	C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -noprofile -executionpolicy Bypass -file D:/Programs/VisualStudio/vcpkg/scripts/buildsystems/msbuild/applocal.ps1 -targetBinary C:/Users/Ivan/source/code/kaban/build/kaban.exe -installedDir D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/debug/bin -OutVariable out

# Rule to build all files generated by this target.
CMakeFiles/kaban.dir/build: kaban.exe
.PHONY : CMakeFiles/kaban.dir/build

CMakeFiles/kaban.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\kaban.dir\cmake_clean.cmake
.PHONY : CMakeFiles/kaban.dir/clean

CMakeFiles/kaban.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Ivan\source\code\kaban C:\Users\Ivan\source\code\kaban C:\Users\Ivan\source\code\kaban\build C:\Users\Ivan\source\code\kaban\build C:\Users\Ivan\source\code\kaban\build\CMakeFiles\kaban.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/kaban.dir/depend

