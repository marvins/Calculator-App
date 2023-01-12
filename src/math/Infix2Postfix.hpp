/**
 * @file    Infix2Postfix.hpp
 * @author  Marvin Smith
 * @date    1/11/2023
 */
#pragma once

// Project Libraries
#include "Operator_Factory.hpp"
#include "Token.hpp"

// C++ Libraries
#include <vector>

/**
 * @brief Convert Postfix to Infix Notation using Shunting Tree algorithm
 */
std::vector<Token> Infix2Postfix_ShuntingYard( const std::vector<Token>& tokens,
                                               Operator_Factory::ptr_t   opfac );

