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
#include <GLFW/glfw3.h> // manually compiled GLFW 3.4

#include "logger.h"
#include "event_system.h"
#include "platform_glfw_events.h"
#include "platform.h"

/************************************************************************
* DEFINES
************************************************************************/
#define UPD_FREQ_HZ         100 // freq for the game logic update [Hz]

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
GLFWwindow* window = NULL; // window object
int quit_ev_handler_id; // handler ID for the Quit Event

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

static void platform_quit(void)
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void keypress_cb(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    es_kb_event keyboard_event;
    keyboard_event.key = translate_keycode(key);

    if (GLFW_PRESS == action)
    {
        keyboard_event.key_state = ES_BUTTON_PRESSED;
    }
    else if (GLFW_RELEASE == action)
    {
        keyboard_event.key_state = ES_BUTTON_RELEASED;
    }

    es_dispatch_kb_event(keyboard_event);
}

static void mouse_btn_cb(GLFWwindow* window, int button, int action, int mods)
{
    switch (button)
    {
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (GLFW_PRESS == action)
            {
                logg_info("RMB pressed");
            }
            else if (GLFW_RELEASE == action)
            {
                logg_info("RMB released");
            }
            break;
        case GLFW_MOUSE_BUTTON_LEFT:
            if (GLFW_PRESS == action)
            {
                logg_info("LMB pressed");
            }
            else if (GLFW_RELEASE == action)
            {
                logg_info("LMB released");
            }
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            if (GLFW_PRESS == action)
            {
                logg_info("MMB pressed");
            }
            else if (GLFW_RELEASE == action)
            {
                logg_info("MMB released");
            }
            break;
        default:
            break;
    }
}

static void cursor_pos_cb(GLFWwindow* window, double xpos, double ypos)
{
    // logg_info("Mouse Coordinates: XPos = %f YPos = %f", xpos, ypos);
}


int platform_init(void)
{
    int ret_val = 0;

    /* Set Hints (pre-init) */
    /* set Platform to Wayland */
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
    /* disable LibDecor */
    glfwInitHint(GLFW_WAYLAND_LIBDECOR, GLFW_WAYLAND_DISABLE_LIBDECOR);

    /* init GLFW */
    if (GLFW_TRUE != glfwInit())
    {
        ret_val = -1;
    }

    quit_ev_handler_id = es_subscribe_quit_event(platform_quit);

    return ret_val;
}

int platform_create_window(const char* title, int width, int height)
{
    int ret_val = 0;

    /* Create window and its OpenGL context */
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (NULL == window)
    {
        glfwTerminate();
        ret_val = -1;
    }
    else
    {
        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Set buffer swap interval to 0 == disable VSync */
        glfwSwapInterval(0);
    }

    return ret_val;
}

void platform_main_loop(pltf_glfw_hooks pltf_hooks)
{
    /* Set cb for key press */
    glfwSetKeyCallback(window, keypress_cb);

    /* Set cb for mouse buttons press */
    glfwSetMouseButtonCallback(window, mouse_btn_cb);

    /* Set cb for cursor position (relative to top-left corner of window) */
    glfwSetCursorPosCallback(window, cursor_pos_cb);

    double old_time;
    double crt_time;
    double time_delta;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();

        /* Get current time */
        crt_time   = glfwGetTime();
        time_delta = crt_time - old_time;

        /* Call update hook with a time delta of UPD_FREQ_HZ */
        if ((1.0f/UPD_FREQ_HZ) <= time_delta)
        {
            pltf_hooks.update_hook(time_delta);
            old_time = crt_time;
        }

        /* Render here -- clear colour buffer to start new frame */
        glClearColor(0.5, 0.4, 0.4, 1.0); // change background colour
        glClear(GL_COLOR_BUFFER_BIT);

        /* Call render hook */
        pltf_hooks.render_hook();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }
}

void platform_deinit(void)
{
    es_unsubscribe_event(quit_ev_handler_id);

    glfwTerminate();
}
