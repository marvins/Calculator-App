/**
 * @file    Engine.hpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#pragma once

// C++ Libraries
#include <memory> 

// Project Libraries
#include "Engine_Config.hpp"

/**
 * @class Engine
 */
class Engine
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<Engine> ptr_t;

        Engine( const Engine_Config& config );

        /**
         * @brief Initialize the Engine
         */
        int Initialize();

        /**
         * @brief Finalize the Engine
         */
        int Finalize();

        /**
         * Run the engine 
         */
        int Run();

    private:

        /// Configuration Info
        Engine_Config m_config;

}; // End of Engine Class
