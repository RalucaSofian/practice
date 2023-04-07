/* @file renderer.c
*
*
*
*
*
*/

/******************
* INCLUDES
******************/
#include <stdio.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

/******************
* GLOBAL VARS
******************/
GLFWwindow* window = NULL; /* window object */


/******************
* FUNC DEFINITIONS
******************/

/*  Init GLFW Lib 
*   return 0 if init was successful
*   return -1 otherwise
*/
int rend_init_glfw(void)
{
    int ret_val = 0;
    
    if (GLFW_TRUE != glfwInit())
    {
        ret_val = -1;
    }

    return ret_val;
}

/*  Create GLFW window and bring it into focus 
*   [in] - window title and window measurements
*   return 0 if creation was successful
*   return -1 otherwise
*/
int rend_create_window(const char* title, int width, int height)
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
    }

    return ret_val;
}

/* Renderer main loop
*  will run until user closes window */
void rend_window_render(void)
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here -- clear colour buffer to start new frame */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

/*  Deinit GLFW Lib */
void rend_deinit_glfw(void)
{
    glfwTerminate();
}

