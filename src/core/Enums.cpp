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


/***************************************************/
/*          Convert Button Type to String          */
/***************************************************/
std::string ButtonTypeToString( ButtonType tp )
{
    switch( tp )
    {
        case ButtonType::NUMBER_0:
            return "NUMBER_0";
        case ButtonType::NUMBER_1:
            return "NUMBER_1";
        case ButtonType::NUMBER_2:
            return "NUMBER_2";
        case ButtonType::NUMBER_3:
            return "NUMBER_3";
        case ButtonType::NUMBER_4:
            return "NUMBER_4";
        case ButtonType::NUMBER_5:
            return "NUMBER_5";
        case ButtonType::NUMBER_6:
            return "NUMBER_6";
        case ButtonType::NUMBER_7:
            return "NUMBER_7";
        case ButtonType::NUMBER_8:
            return "NUMBER_8";
        case ButtonType::NUMBER_9:
            return "NUMBER_9";
        case ButtonType::DECIMAL:
            return "DECIMAL";
        case ButtonType::SOLVE:
            return "SOLVE";
        case ButtonType::MENU:
            return "MENU";
        case ButtonType::PLUS:
            return "PLUS";
        case ButtonType::MINUS:
            return "MINUS";
        case ButtonType::TIMES:
            return "TIMES";
        case ButtonType::DIVIDE:
            return "DIVIDE";
        case ButtonType::POWER:
            return "POWER";
    }
    throw std::runtime_error( "Unsupported value" );
}

/***************************************************/
/*          Convert Button Type to String          */
/***************************************************/
std::string ButtonTypeToScreenText( ButtonType tp )
{
    switch( tp )
    {
        case ButtonType::NUMBER_0:
            return "0";
        case ButtonType::NUMBER_1:
            return "1";
        case ButtonType::NUMBER_2:
            return "2";
        case ButtonType::NUMBER_3:
            return "3";
        case ButtonType::NUMBER_4:
            return "4";
        case ButtonType::NUMBER_5:
            return "5";
        case ButtonType::NUMBER_6:
            return "6";
        case ButtonType::NUMBER_7:
            return "7";
        case ButtonType::NUMBER_8:
            return "8";
        case ButtonType::NUMBER_9:
            return "9";
        case ButtonType::DECIMAL:
            return ".";
        case ButtonType::SOLVE:
            return "=";
        case ButtonType::MENU:
            return "MENU";
        case ButtonType::PLUS:
            return "+";
        case ButtonType::MINUS:
            return "-";
        case ButtonType::TIMES:
            return "x";
        case ButtonType::DIVIDE:
            return "/";
        case ButtonType::POWER:
            return "^";
    }
    throw std::runtime_error( "Unsupported value" );
}

/************************************************/
/*          Convert String to Button Type       */
/************************************************/
ButtonType StringToButtonType( const std::string& tp )
{
    if( tp == "NUMBER_0" )
    {
        return ButtonType::NUMBER_0;
    }
    else if( tp == "NUMBER_1" )
    {
        return ButtonType::NUMBER_1;
    }
    else if( tp == "NUMBER_2" )
    {
        return ButtonType::NUMBER_2;
    }
    else if( tp == "NUMBER_3" )
    {
        return ButtonType::NUMBER_3;
    }
    else if( tp == "NUMBER_4" )
    {
        return ButtonType::NUMBER_4;
    }
    else if( tp == "NUMBER_5" )
    {
        return ButtonType::NUMBER_5;
    }
    else if( tp == "NUMBER_6" )
    {
        return ButtonType::NUMBER_6;
    }
    else if( tp == "NUMBER_7" )
    {
        return ButtonType::NUMBER_7;
    }
    else if( tp == "NUMBER_8" )
    {
        return ButtonType::NUMBER_8;
    }
    else if( tp == "NUMBER_9" )
    {
        return ButtonType::NUMBER_9;
    }
    else if( tp == "DECIMAL" )
    {
        return ButtonType::DECIMAL;
    }
    else if( tp == "SOLVE" )
    {
        return ButtonType::SOLVE;
    }
    else if( tp == "MENU" )
    {
        return ButtonType::MENU;
    }
    else if( tp == "PLUS" )
    {
        return ButtonType::PLUS;
    }
    else if( tp == "MINUS" )
    {
        return ButtonType::MINUS;
    }
    else if( tp == "TIMES" )
    {
        return ButtonType::TIMES;
    }
    else if( tp == "DIVIDE" )
    {
        return ButtonType::DIVIDE;
    }
    else if( tp == "POWER" )
    {
        return ButtonType::POWER;
    }
    else 
    {
        throw std::runtime_error( "Unsupported value (" + tp + ")" );
    }
}

