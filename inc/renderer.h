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
* INCLUDES
************************************************************************/
#include "entity_types.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the Renderer
 */
void REND_Init(void);

/*! @brief Begin the rendering. Set the initial Camera position
 *  @param[in] camera_x - position of the camera on the X axis
 *  @param[in] camera_y - position of the camera on the Y axis
 */
void REND_Begin(double camera_x, double camera_y);

/*! @brief Present onto the screen all of the drawn objects
 */
void REND_PresentScreen(void);

/*! @brief Clear the screen and fill it with a new colour
 *  @param[in] colour - colour to draw the whole screen to
 */
void REND_ClearScreenWithCol(REND_colour colour);

/*! @brief Clear the screen and fill it with a default colour
 */
void REND_ClearScreen(void);

/*! @brief Draw a rectangle. Dimensions in pixels. Origin in the bottom-left corner of window
 *  @param[in] x - coordinate on the X axis from where to start drawing
 *  @param[in] y - coordinate on the Y axis from where to start drawing
 *  @param[in] width - width of the rectangle
 *  @param[in] height - height of the rectangle
 *  @param[in] colour - colour of the rectangle
 */
void REND_DrawRectWithCol(double x, double y, double width, double height, REND_colour colour);

/*! @brief Draw a rectangle in a default colour. Dimensions in pixels. Origin in the bottom-left corner of window
 *  @param[in] x - coordinate on the X axis from where to start drawing
 *  @param[in] y - coordinate on the Y axis from where to start drawing
 *  @param[in] width - width of the rectangle
 *  @param[in] height - height of the rectangle
 */
void REND_DrawRect(double x, double y, double width, double height);

/*! @brief De-initialize the Renderer
 */
void REND_Deinit(void);

#endif // RENDERER_H
