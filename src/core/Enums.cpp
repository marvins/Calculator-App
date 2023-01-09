/**
 * @file    Enums.cpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#include "Enums.hpp"

/**************************************************/
/*          Convert Token-Type to String          */
/**************************************************/
std::string To_String( TOKEN_TYPE tp )
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

    }
    return "UNKNOWN";
}

