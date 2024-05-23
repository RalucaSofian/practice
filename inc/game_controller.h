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
void game_ctrl_init(void);

/*! @brief 
 *  @param[in] time_delta - time delta [sec]
 *  @return
 */
void game_ctrl_update(double time_delta);

/*! @brief
 */
void game_ctrl_render(void);

/*! @brief Deinitialize the Game Controller
 */
void game_ctrl_deinit(void);


#endif // GAME_CONTROLLER_H
