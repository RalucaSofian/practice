/*! @file platform_renderer.h
 *
 *
 *
 *
 *
 */
#ifndef PLATFORM_RENDERER_H
#define PLATFORM_RENDERER_H

/************************************************************************
* INCLUDES
************************************************************************/
#include "entity_types.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the Platform Renderer
 */
void PLATF_RendererInit(void);

/*! @brief Begin the rendering. Set the initial Camera position
 *  @param[in] camera_x - position of the camera on the X axis
 *  @param[in] camera_y - position of the camera on the Y axis
 */
void PLATF_RendererBegin(double camera_x, double camera_y);

/*! @brief Clear the screen and fill it with a new colour
 *  @param[in] colour - colour to draw the whole screen to
 */
void PLATF_RendererClearScreen(REND_colour colour);

/*! @brief Draw a rectangle. Dimensions in pixels. Origin in the bottom-left corner of window
 *  @param[in] x - coordinate on the X axis from where to start drawing
 *  @param[in] y - coordinate on the Y axis from where to start drawing
 *  @param[in] width - width of the rectangle
 *  @param[in] height - height of the rectangle
 *  @param[in] colour - colour of the rectangle
 */
void PLATF_RendererDrawRect(double x, double y, double width, double height, REND_colour colour);

/*! @brief Present onto the screen all of the drawn objects
 */
void PLATF_RendererPresentScreen(void);

/*! @brief De-initialize the Platform Renderer
 */
void PLATF_RendererDeinit(void);

#endif // PLATFORM_RENDERER_H
