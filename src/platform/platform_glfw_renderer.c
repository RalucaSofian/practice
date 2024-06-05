/*! @file platform_renderer.c
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

#include "platform.h"
#include "platform_renderer.h"

int win_width;  // window width
int win_height; // window height

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

void PLATF_RendererInit(void)
{
    glEnable(GL_DEPTH_TEST);

    const GLFWwindow* window = PLATF_GetWindow();
    glfwGetFramebufferSize((GLFWwindow*)window, &win_width, &win_height);

    glViewport(0, 0, win_width, win_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, win_width, 0.0, win_height, -1.0, 5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void PLATF_RendererBegin(double camera_x, double camera_y)
{
    glLoadIdentity();
    glTranslatef(-1*camera_x, -1*camera_y, 0.0);
}

void PLATF_RendererClearScreen(REND_colour colour)
{
    glClearColor(colour.red, colour.green, colour.blue, colour.alpha); // change background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PLATF_RendererDrawRect(double x, double y, double width, double height, REND_colour colour)
{
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);

    glBegin(GL_QUADS);
        glVertex3f(x, y, 0.0);              // Bottom Left
        glVertex3f(x+width, y, 0.0);        // Bottom Right
        glVertex3f(x+width, y+height, 0.0); // Top Right
        glVertex3f(x, y+height, 0.0);       // Top Left
    glEnd();
}

void PLATF_RendererPresentScreen(void)
{
    glFlush();
}

void PLATF_RendererDeinit(void)
{

}
