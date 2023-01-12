#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    1/8/2023
#
#    Purpose:  Build the Math Target
#

#----------------------------------#
#-    Build the Engine Module     -#
#----------------------------------#
add_library( CALC_TGT_ENGN OBJECT 
                    allegro/Allegro_Utilities.cpp 
                    allegro/Allegro_Utilities.hpp
                    Engine.cpp 
                    Engine.hpp 
                    Engine_Config.cpp 
                    Engine_Config.hpp )

