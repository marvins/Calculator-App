/**
 * @file    Options.hpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#pragma once

// C++ Libraries
#include <filesystem>

/**
 * @brief Configuration Class
 */
class Options
{
    public:

        /// Application Name
        std::filesystem::path application_name;

}; // End of Options Class

/**
 * @brief Parse Command-Line
 */
Options  Parse( int argc, char* argv[] );
