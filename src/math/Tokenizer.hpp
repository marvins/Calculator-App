/**
 * @file    Tokenizer.hpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#pragma once

// Project Libraries
#include "Token.hpp"

// C++ Libraries
#include <string>
#include <vector>

/**
 * @brief Tokenize the string
 */
std::vector<Token> Tokenize( const std::string& input );
