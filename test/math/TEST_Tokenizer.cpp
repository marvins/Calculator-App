/**
 * @file    TEST_Tokenizer.cpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#include <gtest/gtest.h>

// Project Libaries
#include <math/Tokenizer.hpp>

// Test Utilities
#include "../unit-test/Unit_Test_Utilities.hpp"

/*******************************************************/
/*          Test the Tokenizer w/ simple string        */
/*******************************************************/
TEST( Tokenizer, Tokenize_Test01 )
{
    // simple string
    std::string input = "3 + 4.3";

    auto opfac = Create_Operator_Factory();

    // Tokenize the input string
    auto tokens = Tokenize( input, opfac );

    // verify there are 3 tokens
    ASSERT_EQ( tokens.size(), 3 );
    ASSERT_EQ( tokens[0].Get_Type(), TOKEN_TYPE::NUMBER );
    ASSERT_EQ( tokens[0].Get_Value(), "3" );

    ASSERT_EQ( tokens[1].Get_Type(), TOKEN_TYPE::OPERATOR_PLUS );

    ASSERT_EQ( tokens[2].Get_Type(), TOKEN_TYPE::NUMBER );
    ASSERT_EQ( tokens[2].Get_Value(), "4.3" );
}
