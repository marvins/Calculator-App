/**
 * @file    Options.cpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#include "Options.hpp"

// Project Libraries
#include "../math/operators/Basic_Operations.hpp"

/************************************************/
/*          Parse the configuration             */
/************************************************/
Options Parse( int argc, char* argv[] )
{
    Options output;

    // Initialize the list of operations
    output.operation_list.push_back( std::make_shared<Operation_Plus>() );

    return output;
}