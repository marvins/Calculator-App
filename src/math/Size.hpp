/**
 * @file    Size.hpp
 * @author  Marvin Smith
 * @date    1/13/2023
 */
#pragma once

// C++ Libraries
#include <sstream>

template <typename TP>
class Size_
{
    public:

        Size_() = default;

        /**
         * @brief Constructor
         */
        Size_( TP width, TP height )
          : m_width( width ), 
            m_height( height )
        {
        }

        /**
         * @brief Get the width 
         */
        TP Width() const
        {
            return m_width;
        }

        /**
         * @brief Get the reference to the width
         */
        TP& Width()
        {
            return m_width;
        }

        /**
         * @brief Get the height
         */
        TP Height() const
        {
            return m_height;
        }

        /**
         * @brief Get the reference to the height
         */
        TP& Height() 
        {
            return m_height;
        }

        /**
         * @brief Addition Operator
         */
        Size_<TP> operator + ( const Size_<TP>& val ) const
        {
            return Size_<TP>( m_width  + val.Width(),
                              m_height + val.Height() );
        }

        /**
         * @brief Subtraction Operator
         */
        template <typename TP2>
        Size_<TP> operator - ( const Size_<TP2>& val ) const
        {
            return Size_<TP>( m_width  - val.Width(),
                              m_height - val.Height() );
        }

        /**
         * @brief Multiplication Operator
         */
        template <typename TP2>
        Size_<TP> operator * ( const TP2& val ) const
        {
           return Size_<TP>( m_width * val,
                             m_height * val );
        }

        /**
         * @brief Division Operator
         */
        template <typename TP2>
        Size_<TP> operator / ( const TP2& val ) const
        {
            return Size_<TP>( m_width / val,
                              m_height / val );
        }

        /**
         * @brief Division Operator
         */
        template <typename TP2>
        Size_<TP> operator / ( const Size_<TP2>& val ) const
        {
            return Size_<TP>( m_width / val.m_width,
                              m_height / val.m_height );
        }

        /**
         * @brief Print to log friendly string
        */
        std::string To_String() const
        {
            std::stringstream sout;
            sout << "Size. W: " << m_width << ", H: " << m_height;
            return sout.str();
        }

    private:

        /// Width
        TP m_width;

        /// Height
        TP m_height;

}; // End of Size class

using Size = Size_<int>; 
