/**
 * @file    Rectangle.hpp
 * @author  Marvin Smith
 * @date    1/14/2023
 */
#pragma once

// Project Libraries
#include "Point.hpp"
#include "Size.hpp"

template <typename TP>
class Rect_
{
    public:

        Rect_() = default;

        /**
         * @brief Parameterized Constructor
        */
        template <typename TP2, typename TP3>
        Rect_( const Point_<TP2,2>& p1, const Point_<TP3,2>& p2 )
          : m_bl( std::min( p1.x(), p2.x() ),
                  std::min( p1.y(), p2.y() ) ),
            m_size( std::abs( p1.x() - p2.x() ), 
                    std::abs( p1.y() - p2.y() ) )
        {
        }

        /**
         * @brief Get the Size of the Rectangle
        */
        Size_<TP> Size() const
        {
            return m_size;
        }

        /**
         * @brief Get the Width of the Rectangle
        */
        TP Width() const
        {
            return m_size.Width();
        }

        /**
         * @brief Get the Height of the Rectangle
        */
        TP Height() const
        {
            return m_size.Height();
        }

        /**
         * @brief Get the Bottom-Left Corner
        */
        Point_<TP,2> bl() const
        {
            return m_bl;
        }

        /**
         * @brief Get the Bottom-Right Corner
        */
        Point_<TP,2> br() const
        {
            return m_bl + Point_<TP,2>( Width(), 0 );
        }

        /**
         * @brief Get the Top-Left Corner
        */
        Point_<TP,2> tl() const
        {
            return m_bl + Point_<TP,2>( 0, Height() );
        }

        /**
         * @brief Get the Top-Right Corner
        */
        Point_<TP,2> tr() const
        {
            return m_bl + Point_<TP,2>( Width(), Height() );
        }

        /**
         * @brief Get the Center Coordinate
        */
        Point_<TP,2> center() const
        {
            return bl() + ( Point_<TP,2>( tr() - bl() ) / 2.0 );
        }

    private:

        /// Bottom-Left Corner
        Point_<TP,2> m_bl; 

        /// Size of Rectangle
        Size_<TP> m_size;

}; // End of Rectangle Class

using RectI = Rect_<int>;
using RectF = Rect_<float>;
using RectD  = Rect_<double>;
using Rect   = RectD;
