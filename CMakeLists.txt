#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    1/8/2022
#
#    Purpose: Build the calculator application
#

cmake_minimum_required( VERSION 3.0 FATAL_ERROR )

#  Set the Project Name
project( Calculator )

#  Custom Tweaks
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

#  Add the executable
add_subdirectory( src )

#  Add the unit-tests
add_subdirectory( test )