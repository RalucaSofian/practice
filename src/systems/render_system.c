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
#include "render_system.h"

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

void RENDSYS_DrawEntity(ENTITY_entity* entity)
{
    if ((NULL == entity) || (NULL == entity->render_info))
    {
        LOGG_warn("Received NULL parameter");
        return;
    }

    REND_DrawRectWithCol(entity->transform.position.x,
                         entity->transform.position.y,
                         entity->transform.width,
                         entity->transform.height,
                         entity->render_info->colour);
}
