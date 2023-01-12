/**
 * @file    Enums.cpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#include "Enums.hpp"

// C++ Libraries
#include <stdexcept>

/**************************************************/
/*          Convert Token-Type to String          */
/**************************************************/
std::string TokenType2String( TOKEN_TYPE tp )
{
    switch(tp)
    {
        case TOKEN_TYPE::UNKNOWN:
            return "UNKNOWN";
        case TOKEN_TYPE::NUMBER:
            return "NUMBER";
        case TOKEN_TYPE::OPERATOR_LPARAM:
            return "OPERATOR_LPARAM";
        case TOKEN_TYPE::OPERATOR_RPARAM:
            return "OPERATOR_RPARAM";
        case TOKEN_TYPE::OPERATOR_PLUS:
            return "OPERATOR_PLUS";
        case TOKEN_TYPE::OPERATOR_MINUS:
            return "OPERATOR_MINUS";
        case TOKEN_TYPE::OPERATOR_TIMES:
            return "OPERATOR_TIMES";
        case TOKEN_TYPE::OPERATOR_DIVIDE:
            return "OPERATOR_DIVIDE";
        case TOKEN_TYPE::OPERATOR_POWER:
            return "OPERATOR_POWER";
        case TOKEN_TYPE::FUNCTION:
            return "FUNCTION";
        default: 
            return "UNKNOWN";
    }
    return "UNKNOWN";
}

/****************************************/
/*          Check if Operator           */
/****************************************/
bool Is_Operator( TOKEN_TYPE tp )
{
    switch(tp)
    {
        case TOKEN_TYPE::OPERATOR_PLUS:
        case TOKEN_TYPE::OPERATOR_MINUS:
        case TOKEN_TYPE::OPERATOR_TIMES:
        case TOKEN_TYPE::OPERATOR_DIVIDE:
        case TOKEN_TYPE::OPERATOR_POWER:
            return true;

        // Error Conditions
        case TOKEN_TYPE::NUMBER:
        case TOKEN_TYPE::OPERATOR_LPARAM:
        case TOKEN_TYPE::OPERATOR_RPARAM:
        case TOKEN_TYPE::UNKNOWN:
        case TOKEN_TYPE::FUNCTION:

        default:
            return false;
    }
}

/****************************************/
/*          Get the Precedence          */
/****************************************/
int Get_Precedence( TOKEN_TYPE tp )
{
    switch(tp)
    {
        case TOKEN_TYPE::OPERATOR_PLUS:
        case TOKEN_TYPE::OPERATOR_MINUS:
            return 2;
        
        case TOKEN_TYPE::OPERATOR_TIMES:
        case TOKEN_TYPE::OPERATOR_DIVIDE:
            return 3;

        case TOKEN_TYPE::OPERATOR_POWER:
            return 4;

        // Error Conditions
        case TOKEN_TYPE::NUMBER:
        case TOKEN_TYPE::OPERATOR_LPARAM:
        case TOKEN_TYPE::OPERATOR_RPARAM:
        case TOKEN_TYPE::FUNCTION:
        case TOKEN_TYPE::UNKNOWN:
        default:
            throw std::runtime_error( "Unsupported Value: " + TokenType2String( tp ) );
    }
}

/********************************************/
/*          Get the Associativity           */
/********************************************/
DIRECTION Get_Associativity( TOKEN_TYPE tp )
{
    switch(tp)
    {
        case TOKEN_TYPE::OPERATOR_PLUS:
        case TOKEN_TYPE::OPERATOR_MINUS:        
        case TOKEN_TYPE::OPERATOR_TIMES:
        case TOKEN_TYPE::OPERATOR_DIVIDE:
            return DIRECTION::LEFT;

        case TOKEN_TYPE::OPERATOR_POWER:
            return DIRECTION::RIGHT;

        // Error Conditions
        case TOKEN_TYPE::NUMBER:
        case TOKEN_TYPE::OPERATOR_LPARAM:
        case TOKEN_TYPE::OPERATOR_RPARAM:
        case TOKEN_TYPE::FUNCTION:
        case TOKEN_TYPE::UNKNOWN:
        default:
            throw std::runtime_error( "Unsupported Value: " + TokenType2String( tp ) );
    }
}