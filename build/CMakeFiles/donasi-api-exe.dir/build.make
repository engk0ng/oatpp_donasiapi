# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/abumuhammad/Documents/C++/qsapi/donasi-api

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/abumuhammad/Documents/C++/qsapi/donasi-api/build

# Include any dependencies generated for this target.
include CMakeFiles/donasi-api-exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/donasi-api-exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/donasi-api-exe.dir/flags.make

CMakeFiles/donasi-api-exe.dir/src/App.cpp.o: CMakeFiles/donasi-api-exe.dir/flags.make
CMakeFiles/donasi-api-exe.dir/src/App.cpp.o: ../src/App.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/abumuhammad/Documents/C++/qsapi/donasi-api/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/donasi-api-exe.dir/src/App.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/donasi-api-exe.dir/src/App.cpp.o -c /Users/abumuhammad/Documents/C++/qsapi/donasi-api/src/App.cpp

CMakeFiles/donasi-api-exe.dir/src/App.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/donasi-api-exe.dir/src/App.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/abumuhammad/Documents/C++/qsapi/donasi-api/src/App.cpp > CMakeFiles/donasi-api-exe.dir/src/App.cpp.i

CMakeFiles/donasi-api-exe.dir/src/App.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/donasi-api-exe.dir/src/App.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/abumuhammad/Documents/C++/qsapi/donasi-api/src/App.cpp -o CMakeFiles/donasi-api-exe.dir/src/App.cpp.s

# Object files for target donasi-api-exe
donasi__api__exe_OBJECTS = \
"CMakeFiles/donasi-api-exe.dir/src/App.cpp.o"

# External object files for target donasi-api-exe
donasi__api__exe_EXTERNAL_OBJECTS =

donasi-api-exe: CMakeFiles/donasi-api-exe.dir/src/App.cpp.o
donasi-api-exe: CMakeFiles/donasi-api-exe.dir/build.make
donasi-api-exe: libdonasi-api-lib.a
donasi-api-exe: /usr/local/lib/oatpp-1.1.0/liboatpp-mongo.a
donasi-api-exe: /usr/local/lib/oatpp-1.1.0/liboatpp-test.a
donasi-api-exe: /usr/local/lib/oatpp-1.1.0/liboatpp.a
donasi-api-exe: /usr/lib/libcrypto.dylib
donasi-api-exe: /usr/local/lib/libmongocxx.3.5.1.dylib
donasi-api-exe: /usr/local/lib/libbsoncxx.3.5.1.dylib
donasi-api-exe: CMakeFiles/donasi-api-exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/abumuhammad/Documents/C++/qsapi/donasi-api/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable donasi-api-exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/donasi-api-exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/donasi-api-exe.dir/build: donasi-api-exe

.PHONY : CMakeFiles/donasi-api-exe.dir/build

CMakeFiles/donasi-api-exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/donasi-api-exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/donasi-api-exe.dir/clean

CMakeFiles/donasi-api-exe.dir/depend:
	cd /Users/abumuhammad/Documents/C++/qsapi/donasi-api/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/abumuhammad/Documents/C++/qsapi/donasi-api /Users/abumuhammad/Documents/C++/qsapi/donasi-api /Users/abumuhammad/Documents/C++/qsapi/donasi-api/build /Users/abumuhammad/Documents/C++/qsapi/donasi-api/build /Users/abumuhammad/Documents/C++/qsapi/donasi-api/build/CMakeFiles/donasi-api-exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/donasi-api-exe.dir/depend

