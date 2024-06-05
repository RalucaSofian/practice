/*! @file player.h
 *
 *
 *
 *
 *
 */
#ifndef PLAYER_SYSTEM_H
#define PLAYER_SYSTEM_H

/************************************************************************
* INCLUDES
************************************************************************/
#include "renderer.h"
#include "entity_types.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the Player object
 */
void PLAYER_Init(void);

/*! @brief Update the Player properties when time_delta expires
 *  @param[in] time_delta - time delta for player updates [sec]
 *  @param[in] entity - player entity that needs to be updated
 */
void PLAYER_Update(double time_delta, ENTITY_entity* entity);

/*! @brief De-initialize the Player object
 */
void PLAYER_Deinit(void);

#endif // PLAYER_SYSTEM_H
