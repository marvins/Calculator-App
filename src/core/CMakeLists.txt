#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    1/8/2023
#
#    Purpose:  Build the Core Target
#

#--------------------------------#
#-    Build the CORE Module     -#
#--------------------------------#
add_library( CALC_TGT_CORE OBJECT 
                    Enums.cpp
                    Enums.hpp
                    Options.cpp
                    Options.hpp )

