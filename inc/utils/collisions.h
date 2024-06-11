/*! @file collisions.h
 *
 *
 *
 *
 *
 */
#ifndef COLLISIONS_H
#define COLLISIONS_H

/************************************************************************
* INCLUDES
************************************************************************/
#include "entity_types.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Get the overlap of two entities on the X axis
 *  @param[in] entity_one - 1st entity to check
 *  @param[in] entity_two - 2nd entity to check
 *  @return meters overlap on the X axis
 */
double COLL_GetEntityOverlapX(ENTITY_entity* entity_one,
                              ENTITY_entity* entity_two);

/*! @brief Get the overlap of two entities on the Y axis
 *  @param[in] entity_one - 1st entity to check
 *  @param[in] entity_two - 2nd entity to check
 *  @return meters overlap on the Y axis
 */
double COLL_GetEntityOverlapY(ENTITY_entity* entity_one,
                              ENTITY_entity* entity_two);

#endif // COLLISIONS_H
