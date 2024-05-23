/*! @file platform_glfw_events.h
 *
 *
 *
 *
 *
 */
#ifndef PLATFORM_GLFW_EVENTS_H
#define PLATFORM_GLFW_EVENTS_H

#include "input_types.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Translate GLFW events into internal events
 *  @param[in] platform_keycode - keycode that needs to be translated
 *  @return translated keycode
 */
key_code translate_keycode(int platform_keycode);

#endif // PLATFORM_GLFW_EVENTS_H
