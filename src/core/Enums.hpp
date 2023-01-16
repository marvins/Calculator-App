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


enum class Window
{
    CALCULATOR = 0,
    
}; // End of Window Enum


enum class ButtonType
{
    NUMBER_0 /*< Number 0 */,
    NUMBER_1 /*< Number 1 */,
    NUMBER_2,
    NUMBER_3,
    NUMBER_4,
    NUMBER_5,
    NUMBER_6,
    NUMBER_7,
    NUMBER_8,
    NUMBER_9,
    DECIMAL,
    SOLVE,
    MENU,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    POWER,
}; // End of Button Enum

/**
 * @brief Convert ButtonType Enum to String
 */
std::string ButtonTypeToString( ButtonType tp );

/**
 * @brief Convert ButtonType to Screen Text
 */
std::string ButtonTypeToScreenText( ButtonType tp );

/**
 * @brief Convert String to ButtonType
 */
ButtonType StringToButtonType( const std::string& tp );
