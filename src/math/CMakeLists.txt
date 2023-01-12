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
                    operators/Basic_Operations.cpp
                    operators/Basic_Operations.hpp 
                    operators/Operation_Base.cpp 
                    operators/Operation_Base.hpp
                    Infix2Postfix.cpp 
                    Infix2Postfix.hpp
                    Operator_Factory.cpp 
                    Operator_Factory.hpp
                    Solver.cpp
                    Solver.hpp
                    Token.cpp
                    Token.hpp
                    Tokenizer.cpp
                    Tokenizer.hpp )

