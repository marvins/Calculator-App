/**
 * @file    Postfix2Infix.hpp
 * @author  Marvin Smith
 * @date    1/11/2023
 */
#pragma once

// Project Libraries
#include "Token.hpp"

// C++ Libraries
#include <vector>

/**
 * @brief Convert Postfix to Infix Notation using Shunting Tree algorithm
 */
std::vector<Token> Postfix2Infix_ShuntingYard( const std::vector<Token>& tokens );
