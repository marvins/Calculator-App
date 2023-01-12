/**
 * @file    Unit_Test_Utilities.cpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#include "Unit_Test_Utilities.hpp"

// Project Libraries
#include <math/operators/Basic_Operations.hpp>

/************************************************/
/*          Create the Operator Factory         */
/************************************************/
Operator_Factory::ptr_t Create_Operator_Factory() 
{
    std::vector<Operation_Base::ptr_t> oplist;
    oplist.push_back( std::make_shared<Operation_Plus>() );
    oplist.push_back( std::make_shared<Operation_Minus>() );
    oplist.push_back( std::make_shared<Operation_Times>() );
    oplist.push_back( std::make_shared<Operation_Divide>() );
    oplist.push_back( std::make_shared<Operation_Power>() );

    auto opfac = std::make_shared<Operator_Factory>( oplist );

    return opfac;
}