/*! @file renderer.h
 *
 *
 *
 *
 *
 */
#ifndef RENDERER_H
#define RENDERER_H

/************************************************************************
* DATA TYPES
************************************************************************/

typedef struct _renderer_colour
{
    double red;
    double green;
    double blue;
    double alpha;
}renderer_colour;

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the Renderer
 */
void renderer_init(void);

void renderer_clear_screen_with_col(renderer_colour colour);

void renderer_clear_screen(void);

void renderer_draw_rect_with_col(double x, double y, double width, double height, renderer_colour colour);

/*! @brief Draw a rectangle
 *  @param[in] x - coordinate on the X axis from where to start drawing
 *  @param[in] y - coordinate on the Y axis from where to start drawing
 *  @param[in] width - width of the rectangle
 *  @param[in] height - height of the rectangle
 */
void renderer_draw_rect(double x, double y, double width, double height);

void renderer_deinit(void);

#endif // RENDERER_H
