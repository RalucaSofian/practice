/*! @file entity_system.h
 *
 *
 *
 *
 *
 */
#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

/************************************************************************
* INCLUDES
************************************************************************/
#include <stdint.h>

#include "entity_types.h"

/************************************************************************
* DEFINES
************************************************************************/
#define STARTING_NO_OF_ENTITIES     2 // number of entities to start with

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize a starting number of entities
 *  @param[in] no_of_entities - initial number of entities
 */
void ENTITY_InitEntities(uint32_t no_of_entities);

/*! @brief Get the current number of entities
 *  @return number of entities
 */
uint32_t ENTITY_GetNoOfEntities(void);

/*! @brief Create a static (non-moving) entity
 *  @param[in] x - coordinate of the entity on the X axis [m]
 *  @param[in] y - coordinate of the entity on the Y axis [m]
 *  @param[in] width - width of the entity [m]
 *  @param[in] height - height of the entity [m]
 *  @param[in] colour - colour of the entity
 *  @return pointer to the newly created entity
 */
ENTITY_entity* ENTITY_CreateStaticEntity(double x, double y,
                                         double width, double height,
                                         REND_colour colour);

/*! @brief Create a player entity
 *  @param[in] x - coordinate of the entity on the X axis [m]
 *  @param[in] y - coordinate of the entity on the Y axis [m]
 *  @param[in] width - width of the entity [m]
 *  @param[in] height - height of the entity [m]
 *  @param[in] colour - colour of the entity
 *  @param[in] player_number - player number
 *  @param[in] key_map - player key map (WASD or Arrows)
 *  @return pointer to the newly created entity
 */
ENTITY_entity* ENTITY_CreatePlayerEntity(double x, double y,
                                         double width, double height,
                                         REND_colour colour,
                                         int player_number, PLAYER_key_map key_map);

/*! @brief Get an entity by its index
 *  @param[in] entity_index - index of entity
 *  @return pointer to the entity
 */
ENTITY_entity* ENTITY_GetEntityByIndex(uint32_t entity_index);

/*! @brief Get an entity by its ID
 *  @param[in] entity_id - ID of entity
 *  @return pointer to the entity
 */
ENTITY_entity* ENTITY_GetEntityById(uint32_t entity_id);

/*! @brief Destroy an entity, based on its ID
 *  @param[in] id - ID of the entity to be destroyed
 */
void ENTITY_DestroyEntityById(uint32_t id);

/*! @brief De-initialize all entities
 */
void ENTITY_DeinitEntities(void);

#endif // ENTITY_SYSTEM_H
