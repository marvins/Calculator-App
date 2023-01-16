/**
 * @file    Session_Context.hpp
 * @author  Marvin Smith
 * @date    1/13/2023
 */
#pragma once

// Project Libraries
#include "../core/Enums.hpp"

class Session_Context
{
    public:

        // Current Window
        Window current_window { Window::CALCULATOR };

        /// Input text
        std::string input_text { "$> 4 + 3 x 7" };

}; // End of Context Class
