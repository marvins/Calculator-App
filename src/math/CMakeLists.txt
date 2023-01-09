#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    1/8/2023
#
#    Purpose:  Build the Math Target
#

#--------------------------------#
#-    Build the MATH Module     -#
#--------------------------------#
add_library( CALC_TGT_MATH OBJECT 
                    Token.cpp
                    Token.hpp
                    Tokenizer.cpp
                    Tokenizer.hpp )

