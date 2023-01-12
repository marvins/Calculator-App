/**
 * @file    TEST_Enums.cpp
 * @author  Marvin Smith
 * @date    1/8/2023 
 */
#include <gtest/gtest.h>

// Project Libraries
#include <core/Enums.hpp>

/************************************************************/
/*          Test the To_String Method for token type        */
/************************************************************/
TEST( Enums, TokenType2String )
{
    ASSERT_EQ( TokenType2String( TOKEN_TYPE::UNKNOWN ),          "UNKNOWN" );
    ASSERT_EQ( TokenType2String( TOKEN_TYPE::NUMBER ),           "NUMBER" );
    ASSERT_EQ( TokenType2String( TOKEN_TYPE::OPERATOR_LPARAM ),  "OPERATOR_LPARAM" );
    ASSERT_EQ( TokenType2String( TOKEN_TYPE::OPERATOR_RPARAM ),  "OPERATOR_RPARAM" );
    ASSERT_EQ( TokenType2String( TOKEN_TYPE::OPERATOR_PLUS ),    "OPERATOR_PLUS" );
    ASSERT_EQ( TokenType2String( TOKEN_TYPE::OPERATOR_MINUS ),   "OPERATOR_MINUS" );
    ASSERT_EQ( TokenType2String( TOKEN_TYPE::OPERATOR_TIMES ),   "OPERATOR_TIMES" );
    ASSERT_EQ( TokenType2String( TOKEN_TYPE::OPERATOR_DIVIDE ),  "OPERATOR_DIVIDE" );
    ASSERT_EQ( TokenType2String( TOKEN_TYPE::OPERATOR_POWER ),   "OPERATOR_POWER" );
    ASSERT_EQ( TokenType2String( TOKEN_TYPE::FUNCTION ),         "FUNCTION" );
}
