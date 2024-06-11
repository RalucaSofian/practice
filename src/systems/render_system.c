/*! @file render_system.c
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
#include "entity_types.h"
#include "renderer.h"
#include "conversions.h"
#include "render_system.h"

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

void RENDSYS_Begin(double camera_x, double camera_y)
{
    REND_Begin(CONV_MetersToPixels(camera_x),
               CONV_MetersToPixels(camera_y));
}

void RENDSYS_PresentScreen(void)
{
    REND_PresentScreen();
}

void RENDSYS_ClearScreenWithCol(REND_colour colour)
{
    REND_ClearScreenWithCol(colour);
}

void RENDSYS_DrawEntity(ENTITY_entity* entity)
{
    if ((NULL == entity) || (NULL == entity->render_info))
    {
        LOGG_warn("Received NULL parameter");
        return;
    }

    REND_DrawRectWithCol(CONV_MetersToPixels(entity->transform.position.x),
                         CONV_MetersToPixels(entity->transform.position.y),
                         CONV_MetersToPixels(entity->transform.width),
                         CONV_MetersToPixels(entity->transform.height),
                         entity->render_info->colour);
}

