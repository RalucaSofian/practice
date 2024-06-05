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

/*! @brief Draw an entity
 *  @param[in] entity - entity that needs to be drawn
 */
void RENDSYS_DrawEntity(ENTITY_entity* entity);

#endif // RENDER_SYSTEM_H
