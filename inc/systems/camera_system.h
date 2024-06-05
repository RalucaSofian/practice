/*! @file camera_system.h
 *
 *
 *
 *
 *
 */
#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

/************************************************************************
* INCLUDES
************************************************************************/
#include "entity_types.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the Camera Controller
 *  @param[in] x - initial position of the camera on the X axis
 *  @param[in] y - initial position of the camera on the Y axis
 */
void CAMERA_Init(double x, double y);

/*! @brief Get the position of the camera on the X axis
 *  @return position of the camera on the X axis
 */
double CAMERA_GetX(void);

/*! @brief Get the position of the camera on the Y axis
 *  @return position of the camera on the Y axis
 */
double CAMERA_GetY(void);

/*! @brief Update the camera position when time_delta expires, depending on the player's position
 *  @param[in] time_delta - time delta for camera updates [sec]
 *  @param[in] player - player render information
 */
void CAMERA_Update(double time_delta, ENTITY_entity* player);

/*! @brief De-initialize the Camera Controller
 */
void CAMERA_Deinit(void);

#endif // CAMERA_SYSTEM_H
