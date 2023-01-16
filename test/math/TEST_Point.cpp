/**
 * @file    TEST_Point.cpp
 * @author  Marvin Smith
 * @date    1/13/2023
 */
#include <gtest/gtest.h>

// Project Libraries
#include <math/Point.hpp>

/************************************/
/*          Constructor Test        */
/************************************/
TEST( Point, Constructors )
{
    Point2d p1;
    ASSERT_NEAR( p1.x(), 0, 0.01 );
    ASSERT_NEAR( p1.y(), 0, 0.01 );

    Point2d p2( 1, 2 );
    ASSERT_NEAR( p2.x(), 1, 0.01 );
    ASSERT_NEAR( p2.y(), 2, 0.01 );
}

/********************************************/
/*          Test the Size Operator          */
/********************************************/
TEST( Point, Size )
{
    Point2d p1;
    ASSERT_EQ( p1.Size(), 2 );

    Point_<int,5> p2;
    ASSERT_EQ( p2.Size(), 5 );
}

/**********************************************/
/*     Test the Point Subtraction Operator    */
/**********************************************/
TEST( Point, Subtraction_Operator )
{
    Point2d p1;
    Point2d p2( 1, 2 );

    auto p3 = p1 - p2;
    ASSERT_NEAR( p3.x(), -1, 0.01 );
    ASSERT_NEAR( p3.y(), -2, 0.01 );
}
