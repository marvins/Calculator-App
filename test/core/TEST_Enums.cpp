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
TEST( Enums, TOKEN_TYPE_To_String )
{
    ASSERT_EQ( To_String( TOKEN_TYPE::UNKNOWN ),          "UNKNOWN" );
    ASSERT_EQ( To_String( TOKEN_TYPE::NUMBER ),           "NUMBER" );
    ASSERT_EQ( To_String( TOKEN_TYPE::OPERATOR_LPARAM ),  "OPERATOR_LPARAM" );
    ASSERT_EQ( To_String( TOKEN_TYPE::OPERATOR_RPARAM ),  "OPERATOR_RPARAM" );
    ASSERT_EQ( To_String( TOKEN_TYPE::OPERATOR_PLUS ),    "OPERATOR_PLUS" );
}
