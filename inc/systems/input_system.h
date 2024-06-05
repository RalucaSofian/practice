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
void INSYS_Init(void);

/*! @brief Get the name of a key as string, based on its key code
 *  @param[in] key_code - keycode for which we need to get the key name
 *  @param[out] key_name - name of the key, as string
 */
void INSYS_GetKeyName(int key_code, const char** key_name);

/*! @brief Get the state of a key (Pressed or Released), based on its key code
 *  @param[in] key_code - keycode for which we need to get the key state
 *  @return state of the key
 */
int INSYS_GetKeyState(INTYPES_key_code key_code);

/*! @brief De-initialize the Input System
 */
void INSYS_Deinit(void);

#endif // INPUT_SYSTEM_H
