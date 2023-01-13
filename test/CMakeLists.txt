#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    1/8/2023
#
#    Purpose:  Build script for unit-tests for calculator application
#

#  Grab the GoogleTest Repo
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG  origin/main
)

FetchContent_MakeAvailable(googletest)

file(GLOB SRCS core/*.cpp math/*.cpp unit-test/*.*pp )

ADD_EXECUTABLE( calculator-tests ${SRCS})

include_directories( "${CMAKE_SOURCE_DIR}/src" )


target_link_libraries(
    calculator-tests
    GTest::gtest_main
    $<TARGET_OBJECTS:CALC_TGT_CORE>
    $<TARGET_OBJECTS:CALC_TGT_MATH>
    ${Boost_LIBRARIES}
    ${Allegro_LIBRARIES}
    ${AllegroFont_LIBRARIES}
)