/*! @file platform_glfw_events.h
 *
 *
 *
 *
 *
 */
#ifndef PLATFORM_GLFW_EVENTS_H
#define PLATFORM_GLFW_EVENTS_H

/************************************************************************
* INCLUDES
************************************************************************/
#include "input_types.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Translate GLFW keycodes into internal keycodes
 *  @param[in] platform_keycode - keycode that needs to be translated
 *  @return translated keycode
 */
INTYPES_key_code PLATF_TranslateKeycode(int platform_keycode);

/*! @brief Translate GLFW mouse button codes into internal button codes
 *  @param[in] platform_btn_code - button code that needs to be translated
 *  @return translated button code
 */
INTYPES_mouse_btns PLATF_TranslateMouseBtnCode(int platform_btn_code);

#endif // PLATFORM_GLFW_EVENTS_H
