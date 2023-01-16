/**
 * @file    Allegro_Utilities.hpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#pragma once

// Allegro API
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// C++ Libraries
#include <memory>

namespace ALLEGRO {

struct Context
{
    typedef std::shared_ptr<Context> ptr_t;

    // Timer Context
    ALLEGRO_TIMER* timer;

    /// Event Queue
    ALLEGRO_EVENT_QUEUE* event_queue;

    /// Display Context
    ALLEGRO_DISPLAY* display;

    /// Desired Primary Font
    ALLEGRO_FONT* font;

}; // End of Context Struct

}; // End of ALLEGRO Namespace
