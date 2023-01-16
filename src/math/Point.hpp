/**
 * @file    Point.hpp
 * @author  Marvin Smith
 * @date    1/13/2023
 */
#pragma once

// C++ Libraries
#include <iostream>
#include <sstream>
#include <string>

/**
 * @class Point_
 */
template <typename TP, int N>
class Point_
{
    public:

        /**
         * @brief Default Constructor
         */
        Point_() = default;

        /**
         * @brief Construction
         * 
         * @param x 
         * @param y
         */
        Point_( const TP& x,
                const TP& y )
        {
            m_data[0] = x;
            m_data[1] = y;
        }

        /**
         * @brief Construction
         * 
         * @param x
         * @param y
         * @param z
         */
        Point_( const TP& x,
                const TP& y,
                const TP& z )
        {
            m_data[0] = x;
            m_data[1] = y;
            m_data[2] = z;
        }

        /**
         * @brief Return the size of the Point
         */
        size_t Size() const
        {
            return N;
        }

        /**
         * @brief Get the X Value
         */
        TP x() const
        {
            return m_data[0];
        }

        /**
         * @brief Get the X Reference
         */
        TP& x()
        {
            return m_data[0];
        } 

        /**
         * @brief Get the Y Value
         */
        TP y() const
        {
            return m_data[1];
        }

        /**
         * @brief Get the Y Reference
         */
        TP& y()
        {
            return m_data[1];
        }

        /**
         * @brief Addition Operator
         */
        Point_<TP,N> operator + ( const Point_<TP,N>& pt ) const
        {
            Point_<TP,N> output;
            for( size_t x = 0; x < Size(); x++ )
            {
                output.m_data[x] = m_data[x] + pt.m_data[x];
            }
            return output;
        }

        /**
         * @brief Subtraction Operator
         */
        Point_<TP,N> operator - ( const Point_<TP,N>& pt ) const
        {
            Point_<TP,N> output;
            for( size_t x = 0; x < Size(); x++ )
            {
                output.m_data[x] = m_data[x] - pt.m_data[x];
            }
            return output;
        }

        /**
         * @brief Multiplication Operator
         */
        template <typename TP2>
        Point_<TP,N> operator * ( const TP2& value )
        {
            Point_<TP,N> output;
            for( size_t x = 0; x < N; x++ )
            {
                output.m_data[x] = m_data[x] * value;
            }
            return output;
        }

        /**
         * @brief Division Operator
         */
        template <typename TP2>
        Point_<TP,N> operator / ( const TP2& value )
        {
            Point_<TP,N> output;
            for( size_t x = 0; x < N; x++ )
            {
                output.m_data[x] = m_data[x] / value;
            }
            return output;
        }

        /**
         * @brief Print to log-friendly string
         */
        std::string To_String() const
        {
            std::stringstream sout;
            sout << "Point<" << N << ">( " << m_data[0];
            for( size_t x = 1; x < Size(); x++ )
            {
                sout << ", " << m_data[x];
            }
            sout << ")";
            return sout.str();
        }

        /// Internal Representation
        std::array<TP,N> m_data { 0 };

}; // End of Point Class

// Common Aliases
using Point2d = Point_<double,2>;
