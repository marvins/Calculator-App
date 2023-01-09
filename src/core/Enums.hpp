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
}; // end of TOKEN_TYPE Enumeration

/**
 * @brief Convert Token-Type to string
 */
std::string To_String( TOKEN_TYPE tp );

/**
 * @brief Convert string to token type
 */
TOKEN_TYPE From_String( const std::string& tp );
