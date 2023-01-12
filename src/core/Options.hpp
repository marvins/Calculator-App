/**
 * @file    Options.hpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#pragma once

// C++ Libraries
#include <filesystem>
#include <vector>

// Project Libraries
#include "../math/operators/Operation_Base.hpp"

/**
 * @brief Configuration Class
 */
class Options
{
    public:

        /// Application Name
        std::filesystem::path application_name;

        /// List of Operators
        std::vector<Operation_Base::ptr_t> operation_list;

}; // End of Options Class

/**
 * @brief Parse Command-Line
 */
Options  Parse( int argc, char* argv[] );
