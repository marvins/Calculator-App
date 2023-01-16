/**
 * @file    Engine.cpp
 * @author  Marvin Smith
 * @date    1/8/2023
 */
#include "Engine.hpp"

// Project Libraries
#include "../core/Logging_Utilities.hpp"
#include "../math/Math_Utilities.hpp"
#include "../math/Point.hpp"
#include "../math/Rectangle.hpp"

// C++ Libraries
#include <sstream>

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
        std::stringstream sout;
        sout << "Failed to initialize allegro";
        BOOST_LOG_TRIVIAL(error) << sout.str();
        return 1;
    }

    if( !al_init_font_addon() )
    {
        std::stringstream sout;
        sout << "Failed to initialize allegro font addon";
        BOOST_LOG_TRIVIAL(error) << sout.str();
        return 1;
    }

    if( !al_init_ttf_addon() )
    {
        std::stringstream sout;
        sout << "Failed to initialize allegro ttf addon";
        BOOST_LOG_TRIVIAL(error) << sout.str();
        return 1;
    }
    

    // Initialize the Primitives Library
    if( !al_init_primitives_addon() )
    {
        std::stringstream sout;
        sout << "Failed to initialize allegro primitives addon";
        BOOST_LOG_TRIVIAL(error) << sout.str();
        return 1;
    }


    // Setup the Keyboard
    al_install_keyboard();

    m_ui_context = std::make_shared<ALLEGRO::Context>();

    m_ui_context->timer       = al_create_timer( 1.0 / 30.0 );
    m_ui_context->event_queue = al_create_event_queue();
    m_ui_context->display     = al_create_display( m_config.Get_Max_Screen_Size().Width(),
                                                   m_config.Get_Max_Screen_Size().Height() );

    m_ui_context->font        = al_load_font("data/fonts/DejaVuSans.ttf", 16, 0);

    al_register_event_source( m_ui_context->event_queue, al_get_keyboard_event_source() );
    al_register_event_source( m_ui_context->event_queue, al_get_display_event_source( m_ui_context->display ) );
    al_register_event_source( m_ui_context->event_queue, al_get_timer_event_source( m_ui_context->timer ) );

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
    int status = 0;

    al_clear_to_color( m_config.Get_Color_Profile().Get_Background_Color() );
    
    // Draw the current screen
    if( m_session_context.current_window == Window::CALCULATOR )
    {
        status = Render_Calculator();
    }

    al_flip_display();

    return status;
}

/********************************************/
/*          Render Calculator Screen        */
/********************************************/
int Engine::Render_Calculator()
{
    // Get current window size
    auto win_size = m_config.Get_Max_Screen_Size();

    // Draw Bounding Rectangle
    float outer_win_offset = 10;
    int divider_width = 6;
    auto tl = Point2d( outer_win_offset, outer_win_offset );
    auto br = Point2d( win_size.Width(), win_size.Height() ) - tl;
    
    al_draw_rounded_rectangle( tl.x(), tl.y(), 
                               br.x(), br.y(), 
                               5, 5,
                               m_config.Get_Color_Profile().Get_Grid_Color(), 
                               divider_width );

    // Render Text / Number Panel
    float window_pct = 0.25;
    int input_panel_bottom_row = win_size.Height() * window_pct;
    auto div_p1 = tl;
    auto div_p2 = br;
    div_p1.y() = input_panel_bottom_row;
    div_p2.y() = input_panel_bottom_row;
    al_draw_line( div_p1.x(), div_p1.y(), div_p2.x(), div_p2.y(), 
                  m_config.Get_Color_Profile().Get_Grid_Color(), 
                  divider_width );

    // Render Grid
    auto key_size = Size( 100, 60 );
    auto key_gap  = 4;
    auto num_keys = ( win_size - Size( outer_win_offset * 2 + key_gap, 
                                       outer_win_offset * 2 + input_panel_bottom_row ) ) / key_size;

    // Compute Center Adjustment for all keys
    auto keybox_size = Size( num_keys.Width()  * key_size.Width(),
                             num_keys.Height() * key_size.Height() + input_panel_bottom_row );
    auto center_adjustment = ( RectD( tl, br ).Size() - keybox_size ) / 2.0;
    

    size_t idx = 0;
    for( int r = 0; r < num_keys.Height(); r++ )
    for( int c = 0; c < num_keys.Width(); c++, idx++ )
    {
        std::string key_text = "?";

        // Bottom-Left 3 col x 4 row block is always the numpad
        if( r > ( num_keys.Height() - 5 ) && ( c < 3 ) )
        {
            if( r == ( num_keys.Height() - 4 ) && ( c == 0 ) ) // 7 key
            {
                key_text = ButtonTypeToScreenText( ButtonType::NUMBER_7 );
            }
            else if( r == ( num_keys.Height() - 4 ) && ( c == 1 ) ) // 8 key
            {
                key_text = ButtonTypeToScreenText( ButtonType::NUMBER_8 );
            }
            else if( r == ( num_keys.Height() - 4 ) && ( c == 2 ) ) // 9 key
            {
                key_text = ButtonTypeToScreenText( ButtonType::NUMBER_9 );
            }
            if( r == ( num_keys.Height() - 3 ) && ( c == 0 ) ) // 4 key
            {
                key_text = ButtonTypeToScreenText( ButtonType::NUMBER_4 );
            }
            else if( r == ( num_keys.Height() - 3 ) && ( c == 1 ) ) // 5 key
            {
                key_text = ButtonTypeToScreenText( ButtonType::NUMBER_5 );
            }
            else if( r == ( num_keys.Height() - 3 ) && ( c == 2 ) ) // 6 key
            {
                key_text = ButtonTypeToScreenText( ButtonType::NUMBER_6 );
            }
            if( r == ( num_keys.Height() - 2 ) && ( c == 0 ) ) // 1 key
            {
                key_text = ButtonTypeToScreenText( ButtonType::NUMBER_1 );
            }
            else if( r == ( num_keys.Height() - 2 ) && ( c == 1 ) ) // 2 key
            {
                key_text = ButtonTypeToScreenText( ButtonType::NUMBER_2 );
            }
            else if( r == ( num_keys.Height() - 2 ) && ( c == 2 ) ) // 3 key
            {
                key_text = ButtonTypeToScreenText( ButtonType::NUMBER_3 );
            }
        }

        auto tl = Point2d( outer_win_offset, 
                           outer_win_offset + input_panel_bottom_row ) 
                + ( Point2d( c * key_size.Width(), 
                             r * key_size.Height()  ) )
                + center_adjustment;
        auto br = tl + key_size;
        al_draw_rounded_rectangle( tl.x(), tl.y(),
                                   br.x(), br.y(),
                                   10, 10, 
                                   m_config.Get_Color_Profile().Get_Grid_Color(), 
                                   divider_width );

        // Draw the text for the specific key
        al_draw_text( m_ui_context->font, 
                      m_config.Get_Color_Profile().Get_Keyboard_Font_Color(),
                      RectD( tl, br ).center().x(), 
                      RectD( tl, br ).center().y(),
                      0, key_text.c_str() );
    }

    // Render input text
    auto input_pos = Point2d( outer_win_offset + 25,
                              ( input_panel_bottom_row - outer_win_offset ) / 2 + outer_win_offset );
    al_draw_text( m_ui_context->font,
                  m_config.Get_Color_Profile().Get_Keyboard_Font_Color(),
                  input_pos.x(), input_pos.y(),
                  0, m_session_context.input_text.c_str() );

    return 0;
}
