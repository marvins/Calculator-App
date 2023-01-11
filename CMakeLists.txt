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

#--------------------------------#
#-          Find Boost          -#
#--------------------------------#
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package( Boost REQUIRED 
                COMPONENTS
                    log )
message( "Boost_FOUND: ${Boost_FOUND}" )
message( "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}" )
message( "Boost_LIBRARIES: ${Boost_LIBRARIES}" )

include_directories( ${Boost_INCLUDE_DIRS} )


#  Add the executable
add_subdirectory( src )

#  Add the unit-tests
add_subdirectory( test )