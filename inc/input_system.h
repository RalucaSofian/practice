/*! @file input_system.h
 *
 *
 *
 *
 *
 */
#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

/************************************************************************
* INCLUDES
************************************************************************/
#include "input_types.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the Input System
 */
void input_sys_init(void);

/*! @brief Get the name of a key as string, based on its key code
 *  @param[in] key_code - keycode for which we need to get the key name
 *  @param[out] key_name - name of the key, as string
 */
void input_sys_get_key_name(int key_code, const char** key_name);

/*! @brief Get the state of a key (Pressed or Released), based on its key code
 *  @param[in] key_code - keycode for which we need to get the key state
 *  @return state of the key
 */
int input_sys_get_key_state(int key_code);

/*! @brief Deinitialize the Input System
 */
void input_sys_deinit(void);

#endif // INPUT_SYSTEM_H
