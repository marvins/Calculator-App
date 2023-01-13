/**
 * @file    Engine.hpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#pragma once

// C++ Libraries
#include <memory>

// Project Libraries
#include "allegro/Allegro_Utilities.hpp"
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

        /**
         * @brief Render the screen 
         */
        int Render_Screen();

    private:

        /// Configuration Info
        Engine_Config m_config;

        /// Allegro Contexts
        ALLEGRO::Context::ptr_t m_ui_context;

        /// Session Context
        Session_Context m_session_context;

}; // End of Engine Class
