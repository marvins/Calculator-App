/**
 * @file    TEST_Rectangle.cpp
 * @author  Marvin Smith
 * @date    1/14/2023
*/
#include <gtest/gtest.h>

// Project Libraries
#include <math/Point.hpp>
#include <math/Rectangle.hpp>

/****************************************/
/*          Test the Constructors       */
/****************************************/
TEST( Rectangle, Constructors )
{
    // Test Default Constructor
    RectD r1;
    ASSERT_NEAR( r1.bl().x(), 0, 0.001 );
    ASSERT_NEAR( r1.bl().y(), 0, 0.001 );
    ASSERT_NEAR( r1.tr().x(), 0, 0.001 );
    ASSERT_NEAR( r1.tr().y(), 0, 0.001 );
    ASSERT_NEAR( r1.Width(), 0, 0.001 );
    ASSERT_NEAR( r1.Height(), 0, 0.001 );
}

/****************************************************/
/*          Test the Center Point Function          */
/****************************************************/
TEST( Rectangle, Center )
{
    RectD r1( Point2d( 2, 2 ), 
              Point2d( 6, 8 ) );

    auto center_r1 = r1.center();

    ASSERT_NEAR( center_r1.x(), 4, 0.001 );
    ASSERT_NEAR( center_r1.y(), 5, 0.001 );
}