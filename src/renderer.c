/*! @file renderer.c
 *
 *
 *
 *
 *
 */

/************************************************************************
* INCLUDES
************************************************************************/
#include <stdio.h>

#include "platform_renderer.h"
#include "renderer.h"

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

void renderer_init(void)
{
    // platform_renderer_init();
}

void renderer_clear_screen_with_col(renderer_colour colour)
{
    // platform_renderer_clear.....
}


void renderer_clear_screen(void)
{
    // renderer_clear_screen_with_col with default colour
}

void renderer_draw_rect_with_col(double x, double y, double width, double height, renderer_colour colour)
{
    //platform_renderer....
}

void renderer_draw_rect(double x, double y, double width, double height)
{
    //our renderer_draw_rect_with_col with default colour
}

void renderer_deinit(void)
{

}
