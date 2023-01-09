/**
 * @file    Token.hpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#pragma once

// Project Libraries
#include "../core/Enums.hpp"

/**
 * @brief Token class
 */
class Token
{
    public:

        Token() = default;

        /**
         * @brief Parameterized Constructor
         */
        Token( TOKEN_TYPE         tp,
               const std::string& value );

        /**
         * @brief Get the Token Type 
         */
        TOKEN_TYPE Get_Type() const;

        /**
         * @brief Get Token Value 
         */
        std::string Get_Value() const;

    private:

        /// Token Type
        TOKEN_TYPE m_type;

        /// Token String
        std::string m_value;

}; // End of Token Class
