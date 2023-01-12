/**
 * @file    Solver.cpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#include "Solver.hpp"

// C++ Libraries
#include <algorithm>
#include <deque>


/************************************/
/*          Solve the Equation      */
/************************************/
Token Solve( const std::vector<Token>& token_list, 
             Operator_Factory::ptr_t   opfac )
{
    // Pop off values until you get to an operator
    std::deque<Token> operand_queue;

    // Create a token stack
    std::deque<Token> tokens( token_list.begin(), token_list.end() );

    while( !tokens.empty() )
    {
        // Clear off all numbers from the list of tokens
        while( tokens.front().Get_Type() == TOKEN_TYPE::NUMBER )
        {
            // Pop off numbers into queue
            operand_queue.push_back( tokens.front() );
            tokens.pop_front();
        }

        // Now we have an operator, process
        auto oper = opfac->Get_Operator( tokens.front() );
        tokens.pop_front();

        // Create argument list
        auto num_operands = oper->Get_Number_Operands();

        std::vector<Token> operands;
        for( int i=0; i < num_operands; i++ )
        {
            operands.push_back( operand_queue.back() );
            operand_queue.pop_back();
        }
        std::reverse( operands.begin(), operands.end() );

        // Run the method
        auto result = oper->Process( operands );

        // Push the result to the end of the operand queue
        operand_queue.push_back( result );
    }

    return operand_queue.back();
}