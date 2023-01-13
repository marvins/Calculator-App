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
    // Initialize Allegro
    if( !al_init() )
    {
        BOOST_LOG_TRIVIAL(error) << "Failed to initialize allegro";
    }

    // Setup the Keyboard
    al_install_keyboard();

    m_ui_context = std::make_shared<ALLEGRO::Context>();

    m_ui_context->timer       = al_create_timer( 1.0 / 30.0 );
    m_ui_context->event_queue = al_create_event_queue();
    m_ui_context->display     = al_create_display( std::get<0>( m_config.Get_Max_Screen_Size() ),
                                                std::get<1>( m_config.Get_Max_Screen_Size() ) );
    m_ui_context->font        = al_create_builtin_font();

    al_register_event_source( m_ui_context->event_queue, al_get_keyboard_event_source() );
    al_register_event_source( m_ui_context->event_queue, al_get_display_event_source( m_context->display ) );
    al_register_event_source( m_ui_context->event_queue, al_get_timer_event_source( m_context->timer ) );

    return 0;
}

/********************************/
/*          Finalize            */
/********************************/
int Engine::Finalize()
{
    // Clean up
    al_destroy_font( m_ui_context->font );
    al_destroy_display( m_ui_context->display );
    al_destroy_timer( m_ui_context->timer );
    al_destroy_event_queue( m_ui_context->event_queue );
    
    m_ui_context = nullptr;

    return 0;
}

/************************************/
/*          Run the Engine          */
/************************************/
int Engine::Run() 
{
    auto status = Initialize();
    if( status ){  return status; }

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer( m_ui_context->timer );
    while(1)
    {
        al_wait_for_event( m_ui_context->event_queue, &event );

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        else if( ( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) )
            break;

        if( redraw && al_is_event_queue_empty( m_ui_context->event_queue ) )
        {

            Render_Screen();

            redraw = false;
        }
    }

    status = Finalize();
    return status;
}

/****************************************/
/*          Render the Screen           */
/****************************************/
int Engine::Render_Screen() 
{
    al_clear_to_color( m_config.Get_Color_Profile().Get_Background_Color() );
    
    // Draw the current screen

    al_flip_display();

    return 0;
}
