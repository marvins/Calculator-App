/**
 * @file    Operator_Factory.hpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#pragma once

// Project Libraries
#include "operators/Operation_Base.hpp"

// C++ Libraries
#include <memory>
#include <vector>

/**
 * @class Operator_Factory
 */
class Operator_Factory
{
    public:

        typedef std::shared_ptr<Operator_Factory> ptr_t;

        /**
         * @brief Construct with list of operations
         */
        Operator_Factory( const std::vector<Operation_Base::ptr_t>& operation_list );

        /**
         * @brief Find the operator for the given token. 
         */
        Operation_Base::ptr_t Get_Operator( const Token& token ) const;

        /**
         * @brief Check if the input string is a valid token 
         */
        bool Is_Operation( const std::string& input ) const;

    private:

        // list of operations
        std::vector<Operation_Base::ptr_t> m_operation_list;

}; // End of Operator_Factory Class
