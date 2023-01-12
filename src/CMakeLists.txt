#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    1/8/2022
#
#    Purpose: Build the calculator application
#

#----------------------------------------#
#-          Build Target Objects        -#
#----------------------------------------#
add_subdirectory( core )
add_subdirectory( math )

#----------------------------------------#
#-          Build the Executable        -#
#----------------------------------------#
add_executable( calculator 
                calculator.cpp
                $<TARGET_OBJECTS:CALC_TGT_CORE>
                $<TARGET_OBJECTS:CALC_TGT_MATH> )

target_link_libraries( calculator 
                       ${Boost_LIBRARIES} )
