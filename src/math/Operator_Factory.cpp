/**
 * @file    Operator_Factory.cpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#include "Operator_Factory.hpp"

/********************************/
/*          Constructor         */
/********************************/
Operator_Factory::Operator_Factory( const std::vector<Operation_Base::ptr_t>& operation_list )
    : m_operation_list( operation_list )
{
}

/****************************************************/
/*          Find an operator for this factory       */
/****************************************************/
Operation_Base::ptr_t Operator_Factory::Get_Operator( const Token& token ) const
{
    // Iterate over each operation
    for( const auto& operation : m_operation_list )
    {
        if( operation->Check( token ) )
        {
            return operation;
        }
    }
    return nullptr;
}

/************************************************************/
/*          Check if the call is a valid operation          */
/************************************************************/
bool Operator_Factory::Is_Operation( const std::string& input ) const
{
    for( const auto& operation : m_operation_list )
    {
        if( operation->Is_Operation( input ) )
        {
            return true;
        }
    }
    return false;
}

