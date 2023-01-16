/**
 * @file    Tokenizer.cpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#include "Tokenizer.hpp"

// Project Libraries
#include "../core/Logging_Utilities.hpp"
#include "../core/String_Utilities.hpp"

// C++ Libraries
#include <algorithm>

/************************************/
/*          Tokenize String         */
/************************************/
std::vector<Token> Tokenize( const std::string&      input_str,
                             Operator_Factory::ptr_t opfac )
{
    std::vector<Token> tokens;
    std::string input = input_str;

    // Convert to lowercase
    std::transform( input_str.cbegin(), 
                    input_str.cend(), 
                    input.begin(), 
                    ::tolower );

    // split the string by spaces for now
    auto parts = String_Split( input, " " ); 

    // Iterate over each part
    for( const auto& part : parts )
    {
        //BOOST_LOG_TRIVIAL(info) << "Part [" << part << "]";

        // Plus Operator
        if( part.size() == 1 && part[0] == '+' )
        {
            tokens.push_back( Token( TOKEN_TYPE::OPERATOR_PLUS ) );
        }

        // Minus Operator
        else if( part.size() == 1 && part[0] == '-' )
        {
            tokens.push_back( Token( TOKEN_TYPE::OPERATOR_MINUS ) );
        }

        // Multiplication Operator
        else if( part.size() == 1 && ( part[0] == '*' || part[0] == 'x' ) )
        {
            tokens.push_back( Token( TOKEN_TYPE::OPERATOR_TIMES ) );
        }

        // Division Operator
        else if( part.size() == 1 && part[0] == '/' )
        {
            tokens.push_back( Token( TOKEN_TYPE::OPERATOR_DIVIDE ) );
        }

        // Power Operator
        else if( part.size() == 1 && part[0] == '^' )
        {
            tokens.push_back( Token( TOKEN_TYPE::OPERATOR_POWER ) );
        }

        // Left Parenthesis
        else if( part.size() == 1 && part[0] == '(' )
        {
            tokens.push_back( Token( TOKEN_TYPE::OPERATOR_LPARAM ) );
        }

        // Right Parenthesis
        else if( part.size() == 1 && part[0] == ')' )
        {
            tokens.push_back( Token( TOKEN_TYPE::OPERATOR_RPARAM ) );
        }

        // Number
        else if( Is_Number( part ) )
        {
            tokens.push_back( Token( TOKEN_TYPE::NUMBER, part ) );
        }

        // Check if Function
        else if( opfac->Is_Operation( part ) )
        {
            tokens.push_back( Token( TOKEN_TYPE::FUNCTION, part ) );
        }

        // Otherwise, error
        else
        {
            throw std::runtime_error( "Unsupported value: " + part );
        }
    }

    return tokens;
}

