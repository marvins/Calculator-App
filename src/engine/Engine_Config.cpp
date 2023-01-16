/**
 * @file    Engine_Config.cpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#include "Engine_Config.hpp"

/************************************************/
/*          Get the Background Color            */
/************************************************/
ALLEGRO_COLOR  Color_Profile::Get_Background_Color() const
{
    return m_background_color;
}

/************************************/
/*          Get Grid Color          */
/************************************/
ALLEGRO_COLOR Color_Profile::Get_Grid_Color() const
{
    return m_grid_color;
}

/************************************************/
/*          Get the Keyboard Font Color         */
/************************************************/
ALLEGRO_COLOR Color_Profile::Get_Keyboard_Font_Color() const
{
    return m_keyboard_font_color;
}

/********************************************/
/*          Get the Max Screen Size         */
/********************************************/
Size Engine_Config::Get_Max_Screen_Size() const
{
    return m_max_screen_size;
}

/********************************************/
/*          Get the Color Profile           */
/********************************************/
Color_Profile  Engine_Config::Get_Color_Profile() const
{
    return m_color_profile;
}
