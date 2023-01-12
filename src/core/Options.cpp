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
    output.operation_list.push_back( std::make_shared<Operation_Minus>() );
    output.operation_list.push_back( std::make_shared<Operation_Times>() );
    output.operation_list.push_back( std::make_shared<Operation_Divide>() );
    output.operation_list.push_back( std::make_shared<Operation_Power>() );

    return output;
}