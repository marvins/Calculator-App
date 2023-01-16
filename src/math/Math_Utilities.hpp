/**
 * @file    Math_Utilities.hpp
 * @author  Marvin Smith
 * @date    1/14/2023
*/
#pragma once

// Project Libraries
#include "Point.hpp"
#include "Size.hpp"

/**
 * @brief Addition Operator
 */
template <typename TP1, typename TP2>
Point_<TP1,2> operator + ( const Point_<TP1,2>& p1, 
                           const Size_<TP2>&    sz )
{
    return Point_<TP1,2>( p1.x() + sz.Width(), 
                          p1.y() + sz.Height() );
}

/**
 * @brief Subtraction Operator
 */
template <typename TP1, typename TP2>
Point_<TP1,2> operator - ( const Point_<TP1,2>& p1, 
                           const Size_<TP2>&    sz )
{
    return Point_<TP1,2>( p1.x() - sz.Width(), 
                          p1.y() - sz.Height() );
}

