/*! @file game_controller.h
 *
 *
 *
 *
 *
 */
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the Game Controller
 */
void GAMECTRL_Init(void);

/*! @brief Update the Game Controller objects
 *  @param[in] time_delta - time delta for updates [sec]
 */
void GAMECTRL_Update(double time_delta);

/*! @brief Render objects on the screen
 */
void GAMECTRL_Render(void);

/*! @brief De-initialize the Game Controller
 */
void GAMECTRL_Deinit(void);

#endif // GAME_CONTROLLER_H
