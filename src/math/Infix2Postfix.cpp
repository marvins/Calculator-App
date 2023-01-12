/**
 * @file    Infix2Postfix.cpp
 * @author  Marvin Smith
 * @date    1/11/2023
 */
#include "Infix2Postfix.hpp"

// C++ Libraries
#include <deque>
#include <stdexcept>

bool Check_Operator_Stack( const Token& token, 
                           const Token& top_operator )
{
    // Top Operator cannot be left parenthesis
    if( top_operator.Get_Type() == TOKEN_TYPE::OPERATOR_LPARAM )
    {
        return false;
    }

    // Token has less precedence than top-operator
    if( Get_Precedence( token.Get_Type() ) < Get_Precedence( top_operator.Get_Type() ) )
    {
        return true;
    }

    // Or same precendence but token is left-associative
    if( Get_Precedence( token.Get_Type() ) == Get_Precedence( top_operator.Get_Type() ) && Get_Associativity( token.Get_Type() ) == DIRECTION::LEFT )
    {
        return true;
    }

    return false;
}

/*************************************************************************************/
/*          Convert Infix to Postfix Notation using Shunting Yard algorithm          */
/*************************************************************************************/
std::vector<Token> Infix2Postfix_ShuntingYard( const std::vector<Token>& tokens,
                                               Operator_Factory::ptr_t   opfac )
{
    std::vector<Token> output_queue;
    std::deque<Token> operator_stack;

    // Iterate over each token
    for( const auto& token : tokens )
    {
        // If token is number, add to output queue
        if( token.Get_Type() == TOKEN_TYPE::NUMBER )
        {
            output_queue.push_back( token );
        }

        // If the token is a function, push to operator stack


        // If the token is an operator
        else if( Is_Operator( token.Get_Type() ) )
        {
            while( !operator_stack.empty() && Check_Operator_Stack( token, operator_stack.front() ) )
            {
                output_queue.push_back( operator_stack.front() );
                operator_stack.pop_front();
            }
            operator_stack.push_front( token );
        }

        // Left Parenthesis
        else if( token.Get_Type() == TOKEN_TYPE::OPERATOR_LPARAM )
        {
            operator_stack.push_front( token );
        }

        // Right parenthasis
        else if( token.Get_Type() == TOKEN_TYPE::OPERATOR_RPARAM )
        {
            while( operator_stack.front().Get_Type() != TOKEN_TYPE::OPERATOR_LPARAM )
            {
                output_queue.push_back( operator_stack.front() );
                operator_stack.pop_front();
            }

            // Pop off the parenthesis and discard it
            operator_stack.pop_front();

            // Check if function is on top
            // TODO
        }

        // Error
        else
        {
            throw std::runtime_error( "Unsupported Token: " + token.To_String() );
        }
    }

    // Pop everything off the operator stack
    while( !operator_stack.empty() )
    {
        output_queue.push_back( operator_stack.front() );
        operator_stack.pop_front();
    }

    return output_queue;
}

