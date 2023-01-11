/**
 * @file    Postfix2Infix.cpp
 * @author  Marvin Smith
 * @date    1/11/2023
 */
#include "Postfix2Infix.hpp"

// C++ Libraries
#include <deque>

/*************************************************************************************/
/*          Convert Postfix to Infix Notation using Shunting Yard algorithm          */
/*************************************************************************************/
std::vector<Token> Postfix2Infix_ShuntingYard( const std::vector<Token>& tokens )
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
    }


}

