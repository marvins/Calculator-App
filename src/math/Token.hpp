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
        Token( TOKEN_TYPE tp );

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
         * @brief Get the token's value
         */
        std::string Get_Value() const;

        /**
         * @brief Get Token Value other than string 
         */
        template<typename TP>
        TP Get_Value() const;


        /**
         * @brief Convert to log-friendly string
         */
        std::string To_String() const;

    private:

        /// Token Type
        TOKEN_TYPE m_type;

        /// Token String
        std::string m_value;

}; // End of Token Class
