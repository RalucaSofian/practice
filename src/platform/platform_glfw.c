/*! @file platform.c
*
*
*
*
*
*/

/************************************************************************
* INCLUDES
************************************************************************/
#include <stdio.h>

#include "logger.h"
#include "event_system.h"
#include "platform_glfw_events.h"
#include "platform.h"

/************************************************************************
* DEFINES
************************************************************************/
#define UPD_FREQ_HZ         100 // freq for the game logic update [Hz]
// #define TIME_UPD

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
GLFWwindow* window = NULL; // window object
int quit_ev_handler_id;    // handler ID for the Quit Event

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

/*! @brief Handler used for reacting to a Quit event */
static void platform_quit(void)
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

/*! @brief Handler used for reacting to keyboard key presses */
static void keypress_cb(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    EVSYS_kb_event keyboard_event;

    keyboard_event.key = PLATF_TranslateKeycode(key);

    if (GLFW_PRESS == action)
    {
        keyboard_event.key_state = KEY_STATE_PRESSED;
    }
    else if (GLFW_RELEASE == action)
    {
        keyboard_event.key_state = KEY_STATE_RELEASED;
    }
    else
    {
        // Ignore keyboard repeat events
        return;
    }

    EVSYS_DispatchKbEvent(keyboard_event);
}

/*! @brief Handler used for reacting to mouse button presses */
static void mouse_btn_cb(GLFWwindow* window, int button, int action, int mods)
{
    switch (button)
    {
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (GLFW_PRESS == action)
            {
                LOGG_info("RMB pressed");
            }
            else if (GLFW_RELEASE == action)
            {
                LOGG_info("RMB released");
            }
            break;
        case GLFW_MOUSE_BUTTON_LEFT:
            if (GLFW_PRESS == action)
            {
                LOGG_info("LMB pressed");
            }
            else if (GLFW_RELEASE == action)
            {
                LOGG_info("LMB released");
            }
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            if (GLFW_PRESS == action)
            {
                LOGG_info("MMB pressed");
            }
            else if (GLFW_RELEASE == action)
            {
                LOGG_info("MMB released");
            }
            break;
        default:
            break;
    }
}

/*! @brief Handler used for reacting to mouse position changes */
static void cursor_pos_cb(GLFWwindow* window, double xpos, double ypos)
{
    // LOGG_info("Mouse Coordinates: XPos = %f YPos = %f", xpos, ypos);
}

/************************************************************************
************************************************************************/
int PLATF_Init(void)
{
    int ret_val = 0;

    // Set Hints (pre-init)
    // set Platform to Wayland
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
    // disable LibDecor
    glfwInitHint(GLFW_WAYLAND_LIBDECOR, GLFW_WAYLAND_DISABLE_LIBDECOR);

    // init GLFW
    if (GLFW_TRUE != glfwInit())
    {
        ret_val = -1;
    }

    quit_ev_handler_id = EVSYS_SubscribeQuitEvent(platform_quit);

    return ret_val;
}

int PLATF_CreateWindow(const char* title, int width, int height)
{
    int ret_val = 0;

    // Create window and its OpenGL context
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (NULL == window)
    {
        glfwTerminate();
        ret_val = -1;
    }
    else
    {
        // Make the window's context current
        glfwMakeContextCurrent(window);

        // Set buffer swap interval to 0 == disable VSync
        glfwSwapInterval(0);
    }

    return ret_val;
}

void PLATF_MainLoop(PLATF_glfw_hooks pltf_hooks)
{
    // Set cb for key press
    glfwSetKeyCallback(window, keypress_cb);

    // Set cb for mouse buttons press
    glfwSetMouseButtonCallback(window, mouse_btn_cb);

    // Set cb for cursor position (relative to top-left corner of window)
    glfwSetCursorPosCallback(window, cursor_pos_cb);

    double old_time;
    double crt_time;
    double time_delta;
    
    #ifdef TIME_UPD
        double upd_start_time;
    #endif

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Poll for and process events
        glfwPollEvents();

        // Get current time
        crt_time   = glfwGetTime();
        time_delta = crt_time - old_time;

        // Call update hook with a time delta of UPD_FREQ_HZ
        if ((1.0f/UPD_FREQ_HZ) <= time_delta)
        {
            #ifdef TIME_UPD
                upd_start_time = glfwGetTime();
            #endif
            
            pltf_hooks.update_hook(time_delta);
            
            #ifdef TIME_UPD
                LOGG_info("Upd Hook Duration: %f us", (glfwGetTime()-upd_start_time)*1000000);
            #endif
            old_time = crt_time;
        }

        // Call render hook
        pltf_hooks.render_hook();

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }
}

const GLFWwindow* PLATF_GetWindow(void)
{
    return (const GLFWwindow*)window;
}

double PLATF_GetWindowWidth(void)
{
    int win_width = 0;
    glfwGetWindowSize(window, &win_width, NULL);

    return (double)win_width;
}

double PLATF_GetWindowHeight(void)
{
    int win_height = 0;
    glfwGetWindowSize(window, NULL, &win_height);

    return (double)win_height;
}

void PLATF_Deinit(void)
{
    EVSYS_UnsubscribeEvent(quit_ev_handler_id);

    glfwTerminate();
}
