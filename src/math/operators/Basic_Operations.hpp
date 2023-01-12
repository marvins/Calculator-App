/**
 * @file    Basic_Operations.hpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#pragma once

// Project Libraries
#include "Operation_Base.hpp"

/**
 * @class Operation_Plus
 */
class Operation_Plus : public Operation_Base
{
    public:

        /**
         * @brief Get the number of operands necessary
         */
        int Get_Number_Operands() const override;

        /**
         * @brief Perform Addition
         */
        Token Process( const std::vector<Token>& values ) const override;

        /**
         * @brief Check the token
         */
        bool Check( const Token& token ) const override;

        /**
         * @brief Check the command name
         */
        bool Is_Operation( const std::string& command ) const override;

}; // End of Operation_Plus Class

/**
 * @class Operation_Minus
 */
class Operation_Minus : public Operation_Base
{
    public:

        /**
         * @brief Get the number of operands necessary
         */
        int Get_Number_Operands() const override;

        /**
         * @brief Perform Addition
         */
        Token Process( const std::vector<Token>& values ) const override;

        /**
         * @brief Check the token
         */
        bool Check( const Token& token ) const override;

        /**
         * @brief Check the command name
         */
        bool Is_Operation( const std::string& command ) const override;

}; // End of Operation_Minus Class

/**
 * @class Operation_Times
 */
class Operation_Times : public Operation_Base
{
    public:

        /**
         * @brief Get the number of operands necessary
         */
        int Get_Number_Operands() const override;

        /**
         * @brief Perform Addition
         */
        Token Process( const std::vector<Token>& values ) const override;

        /**
         * @brief Check the token
         */
        bool Check( const Token& token ) const override;

        /**
         * @brief Check the command name
         */
        bool Is_Operation( const std::string& command ) const override;

}; // End of Operation_Times Class


/**
 * @class Operation_Divide
 */
class Operation_Divide : public Operation_Base
{
    public:

        /**
         * @brief Get the number of operands necessary
         */
        int Get_Number_Operands() const override;

        /**
         * @brief Perform Addition
         */
        Token Process( const std::vector<Token>& values ) const override;

        /**
         * @brief Check the token
         */
        bool Check( const Token& token ) const override;

        /**
         * @brief Check the command name
         */
        bool Is_Operation( const std::string& command ) const override;

}; // End of Operation_Divide Class

/**
 * @class Operation_Power
 */
class Operation_Power : public Operation_Base
{
    public:

        /**
         * @brief Get the number of operands necessary
         */
        int Get_Number_Operands() const override;

        /**
         * @brief Perform Addition
         */
        Token Process( const std::vector<Token>& values ) const override;

        /**
         * @brief Check the token
         */
        bool Check( const Token& token ) const override;

        /**
         * @brief Check the command name
         */
        bool Is_Operation( const std::string& command ) const override;

}; // End of Operation_Power Class

