/**
 * @file    Solver.hpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#pragma once


// Project Libraries
#include "Operator_Factory.hpp"
#include "Token.hpp"

// C++ Libraries
#include <vector>

/**
 * @brief Solve the input equation
 *
 * @param tokens Set of tokens in RPM format!
 */
Token Solve( const std::vector<Token>& tokens, 
             Operator_Factory::ptr_t   opfac );
