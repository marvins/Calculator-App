/**
 * @file    Operation_Base.hpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#pragma once

// C++ Libraries
#include <memory>
#include <vector>

// Project Libraries
#include "../Token.hpp"

/**
 * @class Operation_Base
 */
class Operation_Base
{
    public:

        typedef std::shared_ptr<Operation_Base> ptr_t; 

        /**
         * @brief Get the required number of operands
         */
        virtual int Get_Number_Operands() const = 0;

        /**
         * @brief Perform the operation
         */
        virtual Token Process( const std::vector<Token>& values ) const = 0;

        /**
         * @brief Check the Token
         */
        virtual bool Check( const Token& token ) const = 0;

        /**
         * @brief Check if a string is a valid operation
         */
        virtual bool Is_Operation( const std::string& command ) const = 0;

}; // End of Class Operation_Base
