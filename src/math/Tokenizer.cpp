/**
 * @file    Tokenizer.cpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#include "Tokenizer.hpp"

// C++ Libraries
#include <algorithm>

/************************************/
/*          Tokenize String         */
/************************************/
std::vector<Token> Tokenize( const std::string& input_str )
{
    std::vector<Token> tokens;
    std::string input;

    // Convert to lowercase
    std::transform( input_str.begin(), 
                    input_str.end(), 
                    input.begin(), 
                    ::tolower );

    // split the string by spaces for now

    return tokens;
}

