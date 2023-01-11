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
                    Logging_Utilities.cpp 
                    Logging_Utilities.hpp
                    Options.cpp
                    Options.hpp
                    String_Utilities.cpp
                    String_Utilities.hpp )

