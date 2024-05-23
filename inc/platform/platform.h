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
* DATA TYPES
************************************************************************/

/*! @brief Function pointer type for update functions
 */
typedef void (* pltf_update_func)(double time_delta);

/*! @brief Function pointer type for render functions
 */
typedef void (* pltf_render_func)(void);


/*! @brief Structure of the platform hooks
 */
typedef struct _pltf_glfw_hooks
{
    pltf_update_func update_hook;
    pltf_render_func render_hook;

}pltf_glfw_hooks;

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Init GLFW Lib
 *  @return 0 if init was successful, -1 otherwise
 */
int platform_init(void);

/*! @brief Create GLFW window and bring it into focus
 *  @param[in] title  - window title
 *  @param[in] width  - window width in pixels
 *  @param[in] height - window height in pixels
 *  @return 0 if creation was successful, -1 otherwise
 */
int platform_create_window(const char* title, int width, int height);

/*! @brief Platform main loop. Will run and render until user closes window
 */
void platform_main_loop(pltf_glfw_hooks pltf_hooks);

/*! @brief Deinit GLFW Lib
 */
void platform_deinit(void);

#endif /* PLATFORM_H */
