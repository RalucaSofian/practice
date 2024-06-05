/*! @file platform.h
*
*
*
*
*
*/
#ifndef PLATFORM_H
#define PLATFORM_H

/************************************************************************
* INCLUDES
************************************************************************/
#include <GLFW/glfw3.h> // manually compiled GLFW 3.4

/************************************************************************
* DATA TYPES
************************************************************************/

/*! @brief Function pointer type for update functions
 */
typedef void (* PLATF_update_func)(double time_delta);

/*! @brief Function pointer type for render functions
 */
typedef void (* PLATF_render_func)(void);


/*! @brief Structure of the platform hooks
 */
typedef struct _PLATF_glfw_hooks
{
    PLATF_update_func update_hook;
    PLATF_render_func render_hook;

}PLATF_glfw_hooks;

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Initialize the GLFW Library
 *  @return 0 if init was successful, -1 otherwise
 */
int PLATF_Init(void);

/*! @brief Create GLFW window and bring it into focus
 *  @param[in] title  - window title
 *  @param[in] width  - window width in pixels
 *  @param[in] height - window height in pixels
 *  @return 0 if creation was successful, -1 otherwise
 */
int PLATF_CreateWindow(const char* title, int width, int height);

/*! @brief Platform main loop. Will run and render until user closes window
 */
void PLATF_MainLoop(PLATF_glfw_hooks pltf_hooks);

/*! @brief Get a pointer to the currently active window
 *  @return pointer to the active window
 */
const GLFWwindow* PLATF_GetWindow(void);

/*! @brief Get the width of the currently active window
 *  @return window width in pixels
 */
int PLATF_GetWindowWidth(void);

/*! @brief Get the height of the currently active window
 *  @return window height in pixels
 */
int PLATF_GetWindowHeight(void);

/*! @brief De-initialize the GLFW Library
 */
void PLATF_Deinit(void);

#endif // PLATFORM_H
