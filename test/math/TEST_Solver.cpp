/**
 * @file    TEST_Solver.cpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#include <gtest/gtest.h>

// Project Libraries
#include <math/Infix2Postfix.hpp>
#include <math/Solver.hpp>
#include <math/Tokenizer.hpp>

// Test Libraries
#include "../unit-test/Unit_Test_Utilities.hpp"


/****************************************************/
/*          Test the Solver on Complex Equation     */
/****************************************************/
TEST( Solver, Solve_Test_01 )
{
    // simple string
    std::string input = " 3 + 4 x 2 / ( 1 - 5 ) ^ 2 ^ 3";

    // Create Operator Factory
    auto opfac = Create_Operator_Factory();

    // Tokenize the input string
    auto tokens_infix = Tokenize( input, opfac );
    
    // Test the Infix2Postfix
    auto tokens_postfix = Infix2Postfix_ShuntingYard( tokens_infix, opfac );

    // Solve
    auto result = Solve( tokens_postfix,
                         opfac );

    std::cout << "Result: " << result.To_String() << std::endl;
    ASSERT_NEAR( result.Get_Value<double>(), 3.0001, 0.0001 );

}