/**
 * @file    Engine.cpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#include "Engine.hpp"

// Project Libraries
#include "../core/Logging_Utilities.hpp"


/********************************/
/*          Constructor         */
/********************************/
Engine::Engine( const Engine_Config& config )
  : m_config( config )
{
}

/********************************/
/*          Initialize          */
/********************************/
int Engine::Initialize()
{
    if( !al_init() )
    {
        BOOST_LOG_TRIVIAL(error) << "Failed to initialize allegro";
    }

    return 0;
}

/********************************/
/*          Finalize            */
/********************************/
int Engine::Finalize()
{
    // Clean up
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
    
    return 0;
}

/************************************/
/*          Run the Engine          */
/************************************/
int Engine::Run() 
{
    auto status = Initialize();
    if( status ){  return status; }



    status = Finalize();
    return status;
}