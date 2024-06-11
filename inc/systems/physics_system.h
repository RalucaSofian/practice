/*! @file physics_system.h
 *
 *
 *
 *
 *
 */
#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

/************************************************************************
* INCLUDES
************************************************************************/
#include "entity_types.h"
#include "vector.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the Physics System
 */
void PHYS_Init(void);

/*! @brief Reset the force that was applied on an entity
 *  @param[in] entity - entity whose force needs to be reset
 */
void PHYS_ResetForce(ENTITY_entity* entity);

/*! @brief Apply a force on an entity
 *  @param[in] entity - entity that needs to be updated
 *  @param[in] force - force that needs to be applied [2D vector]
 */
void PHYS_ApplyForce(ENTITY_entity* entity, vec2 force);

/*! @brief Apply all the default forces on an entity
 *  @param[in] entity - entity that needs to be updated
 */
void PHYS_ApplyDefaultForces(ENTITY_entity* entity);

/*! @brief Update the entity's physics properties when time_delta expires
 *  @param[in] time_delta - time delta for entity updates [sec]
 *  @param[in] entity - entity that needs to be updated
 */
void PHYS_UpdateEntity(double time_delta, ENTITY_entity* entity);

/*! @brief De-initialize the Physics System
 */
void PHYS_Deinit(void);

#endif // PHYSICS_SYSTEM_H
