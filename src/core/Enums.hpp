/**
 * @file    Enums.hpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#pragma once

// C++ Libraries
#include <cinttypes>
#include <string>

/**
 * @brief Describes the type of token 
 */
enum class TOKEN_TYPE
{
    UNKNOWN         = -1,
    NUMBER          = 0,
    OPERATOR_LPARAM = 1,
    OPERATOR_RPARAM = 2,
    OPERATOR_PLUS   = 3,
    OPERATOR_MINUS  = 4,
    OPERATOR_TIMES  = 5,
    OPERATOR_DIVIDE = 6,
    OPERATOR_POWER  = 7,
    FUNCTION        = 8,
}; // end of TOKEN_TYPE Enumeration

/**
 * @brief Convert Token-Type to string
 */
std::string TokenType2String( TOKEN_TYPE tp );

/**
 * @brief Check if Token-Type is an operator
 */
bool Is_Operator( TOKEN_TYPE tp );

/**
 * @brief Convert string to token type
 */
TOKEN_TYPE String2TokenType( const std::string& tp );

int Get_Precedence( TOKEN_TYPE tp );

enum class DIRECTION
{
    UNKNOWN /*< Error condition only */,
    LEFT,
    RIGHT,
}; // end of enum ASSOCIATIVITY

DIRECTION Get_Associativity( TOKEN_TYPE tp );
