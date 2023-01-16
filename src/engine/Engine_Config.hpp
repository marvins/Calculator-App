/**
 * @file    Engine_Config.hpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#pragma once

// Allegro API
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

// C++ Libraries
#include <tuple>

// Project Libraries
#include "../math/Point.hpp"
#include "../math/Size.hpp"

class Color_Profile
{
    public:

        /**
         * @brief Get the Global Background Color
         */
        ALLEGRO_COLOR Get_Background_Color() const;

        /**
         * @brief Get the Calculator's Grid Color
         */
        ALLEGRO_COLOR Get_Grid_Color() const;

        /**
         * @brief Get the Keyboard Font Color
        */
        ALLEGRO_COLOR Get_Keyboard_Font_Color() const;

    private:

        ALLEGRO_COLOR m_background_color { al_map_rgb( 0, 0, 0 ) };

        ALLEGRO_COLOR m_grid_color { al_map_rgb( 13, 91, 116 ) };

        ALLEGRO_COLOR m_keyboard_font_color { al_map_rgb( 255, 255, 255 ) };

}; // End of Color_Profile Struct

/**
 * @class Engine_Config
 */
class Engine_Config
{
    public:

        Engine_Config() = default;

        /**
         * @brief Get the Maximum Screen Size
         */
        Size Get_Max_Screen_Size() const;

        /**
         * @brief Get the Color Profile
         */
        Color_Profile Get_Color_Profile() const;

    private:

        /// Screen Size
        Size m_max_screen_size { 640, 480 };

        /// Color Profile
        Color_Profile m_color_profile; 

}; // End of Engine_Config Class
