/**
 * @file    calculator.cpp
 * @author  Marvin Smith
 * @date    1/8/2023
 *
 * @brief Allegro-based C++ calculator application 
 */

// C++ Libraries
#include <iostream>

// Project Libraries
#include "core/Options.hpp"
#include "engine/Engine.hpp"
#include "math/Operator_Factory.hpp"


int main( int argc, char* argv[] )
{
    // Parse the command-line options
    auto options = Parse( argc, argv );

    // Build the Operator Factory
    auto opfac = std::make_shared<Operator_Factory>( options.operation_list );

    // Construct the UI
    auto engine = std::make_shared<Engine>( options.engine_config );

    return engine->Run();
}