/*! @file platform_renderer.h
 *
 *
 *
 *
 *
 */
#ifndef PLATFORM_RENDERER_H
#define PLATFORM_RENDERER_H

#include "renderer.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

void platform_renderer_init(void);

void platform_renderer_clear_screen(renderer_colour colour);

void platform_renderer_draw_rect(double x, double y, double width, double height, renderer_colour colour);

void platform_renderer_deinit(void);

#endif // PLATFORM_RENDERER_H
