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

#include "logger.h"
#include "platform_renderer.h"
#include "renderer.h"

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

void REND_Init(void)
{
    PLATF_RendererInit();
}

void REND_Begin(double camera_x, double camera_y)
{
    PLATF_RendererBegin(camera_x, camera_y);
}

void REND_PresentScreen(void)
{
    PLATF_RendererPresentScreen();
}

void REND_ClearScreenWithCol(REND_colour colour)
{
    PLATF_RendererClearScreen(colour);
}

void REND_ClearScreen(void)
{
    REND_colour default_clear_col = {0};

    default_clear_col.red   = 1.0;
    default_clear_col.green = 1.0;
    default_clear_col.blue  = 1.0;
    default_clear_col.alpha = 1.0;

    REND_ClearScreenWithCol(default_clear_col);
}

void REND_DrawRectWithCol(double x, double y, double width, double height, REND_colour colour)
{
    PLATF_RendererDrawRect(x, y, width, height, colour);
}

void REND_DrawRect(double x, double y, double width, double height)
{
    REND_colour default_red_col = {0};

    default_red_col.red   = 1.0;
    default_red_col.green = 0.0;
    default_red_col.blue  = 0.0;
    default_red_col.alpha = 1.0;

    PLATF_RendererDrawRect(x, y, width, height, default_red_col);
}

void REND_DrawLineWithCol(double a_x, double a_y, double b_x, double b_y, REND_colour colour)
{
    PLATF_RendererDrawLine(a_x, a_y, b_x, b_y, colour);
}

void REND_Deinit(void)
{

}
