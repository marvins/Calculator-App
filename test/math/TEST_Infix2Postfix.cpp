/**
 * @file    TEST_Infix2Postfix.cpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#include <gtest/gtest.h>

// Project Libaries
#include <core/Logging_Utilities.hpp>
#include <math/Infix2Postfix.hpp>
#include <math/Tokenizer.hpp>

// Test Utilities
#include "../unit-test/Unit_Test_Utilities.hpp"

/***********************************************************/
/*          Test the Infix2Postfix w/ simple string        */
/***********************************************************/
TEST( Infix2Postfix, Infix2Postfix_ShuntingYard_Test01 )
{
    // simple string
    std::string input = "3 + 4.3";

    auto opfac = Create_Operator_Factory();

    // Tokenize the input string
    auto tokens_infix = Tokenize( input, opfac );
    
    // Test the Infix2Postfix
    auto tokens_postfix = Infix2Postfix_ShuntingYard( tokens_infix, opfac );

    ASSERT_EQ( tokens_postfix.size(), 3 );
    ASSERT_EQ( tokens_postfix[0].Get_Value(), "3" );
    ASSERT_EQ( tokens_postfix[1].Get_Value(), "4.3" );
    ASSERT_EQ( tokens_postfix[2].Get_Type(), TOKEN_TYPE::OPERATOR_PLUS );
}

/****************************************************************/
/*          Test the Infix2Postfix w/ less simple string        */
/****************************************************************/
TEST( Infix2Postfix, Infix2Postfix_ShuntingYard_Test02 )
{
    // simple string
    std::string input = "3 + 4.3 x 7";

    auto opfac = Create_Operator_Factory();

    // Tokenize the input string
    auto tokens_infix = Tokenize( input, opfac );
    
    // Test the Infix2Postfix
    auto tokens_postfix = Infix2Postfix_ShuntingYard( tokens_infix, opfac );

    ASSERT_EQ( tokens_postfix.size(), 5 );
    ASSERT_EQ( tokens_postfix[0].Get_Value(), "3" );
    ASSERT_EQ( tokens_postfix[1].Get_Value(), "4.3" );
    ASSERT_EQ( tokens_postfix[2].Get_Value(), "7" );
    ASSERT_EQ( tokens_postfix[3].Get_Type(), TOKEN_TYPE::OPERATOR_TIMES );
    ASSERT_EQ( tokens_postfix[4].Get_Type(), TOKEN_TYPE::OPERATOR_PLUS );
}

/*********************************************************************/
/*          Test the Infix2Postfix w/ much less simple string        */
/*********************************************************************/
TEST( Infix2Postfix, Infix2Postfix_ShuntingYard_Test03 )
{
    // simple string
    std::string input = " 3 + 4 x 2 / ( 1 - 5 ) ^ 2 ^ 3";

    auto opfac = Create_Operator_Factory();

    // Tokenize the input string
    auto tokens_infix = Tokenize( input, opfac );
    
    // Test the Infix2Postfix
    auto tokens_postfix = Infix2Postfix_ShuntingYard( tokens_infix, opfac );

    ASSERT_EQ( tokens_postfix.size(), 13 );
    ASSERT_EQ( tokens_postfix[0].Get_Value(), "3" );
    ASSERT_EQ( tokens_postfix[1].Get_Value(), "4" );
    ASSERT_EQ( tokens_postfix[2].Get_Value(), "2" );
    ASSERT_EQ( tokens_postfix[3].Get_Type(), TOKEN_TYPE::OPERATOR_TIMES );
    ASSERT_EQ( tokens_postfix[4].Get_Value(), "1" );
    ASSERT_EQ( tokens_postfix[5].Get_Value(), "5" );
    ASSERT_EQ( tokens_postfix[6].Get_Type(), TOKEN_TYPE::OPERATOR_MINUS );
    ASSERT_EQ( tokens_postfix[7].Get_Value(), "2" );
    ASSERT_EQ( tokens_postfix[8].Get_Value(), "3" );
    ASSERT_EQ( tokens_postfix[9].Get_Type(), TOKEN_TYPE::OPERATOR_POWER );
    ASSERT_EQ( tokens_postfix[10].Get_Type(), TOKEN_TYPE::OPERATOR_POWER );
    ASSERT_EQ( tokens_postfix[11].Get_Type(), TOKEN_TYPE::OPERATOR_DIVIDE );
    ASSERT_EQ( tokens_postfix[12].Get_Type(), TOKEN_TYPE::OPERATOR_PLUS );
}
