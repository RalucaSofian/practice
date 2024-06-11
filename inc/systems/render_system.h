/*! @file render_system.h
 *
 *
 *
 *
 *
 */
#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

/************************************************************************
* INCLUDES
************************************************************************/
#include "entity_system.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Begin the rendering. Set the initial Camera position
 *  @param[in] camera_x - position of the camera on the X axis [m]
 *  @param[in] camera_y - position of the camera on the Y axis [m]
 */
void RENDSYS_Begin(double camera_x, double camera_y);

/*! @brief Present onto the screen all of the drawn objects
 */
void RENDSYS_PresentScreen(void);

/*! @brief Clear the screen and fill it with a new colour
 *  @param[in] colour - colour to draw the whole screen to
 */
void RENDSYS_ClearScreenWithCol(REND_colour colour);

/*! @brief Draw an entity
 *  @param[in] entity - entity that needs to be drawn
 */
void RENDSYS_DrawEntity(ENTITY_entity* entity);

#endif // RENDER_SYSTEM_H
