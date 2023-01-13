/**
 * @file    Engine_Config.hpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#pragma once

// Allegro API
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

// C++ Libraries
#include <tuple>

class Color_Profile
{
    public:

        ALLEGRO_COLOR Get_Background_Color() const;

    private:

        ALLEGRO_COLOR m_background_color { al_map_rgb( 0, 0, 0 ) };

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
        std::tuple<int,int> Get_Max_Screen_Size() const;

        /**
         * @brief Get the Color Profile
         */
        Color_Profile Get_Color_Profile() const;

    private:

        /// Screen Size
        std::tuple<int,int> m_max_screen_size { std::make_tuple( 640, 480 ) };

        /// Color Profile
        Color_Profile m_color_profile; 

}; // End of Engine_Config Class
