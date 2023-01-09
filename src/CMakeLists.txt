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
#-          Calculator Sources          -#
#----------------------------------------#
set( CALC_SOURCES
    engine/Engine.cpp
    engine/Engine.hpp
    math/Token.cpp
    math/Token.hpp
    math/Tokenizer.cpp
    math/Tokenizer.hpp
    calculator.cpp 
)

#----------------------------------------#
#-          Build the Executable        -#
#----------------------------------------#
add_executable( calculator ${CALC_SOURCES}
                $<TARGET_OBJECTS:CALC_TGT_CORE> )


