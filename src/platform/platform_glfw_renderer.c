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
#include <GLFW/glfw3.h>

#include "platform.h"
#include "platform_renderer.h"

int win_width;  // window width [px]
int win_height; // window height [px]

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

void PLATF_RendererDrawLine(double a_x, double a_y, double b_x, double b_y, REND_colour colour)
{
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);

    glBegin(GL_LINES);
        glVertex3f(a_x, a_y, 1.0); // point (a_x; a_y)
        glVertex3f(b_x, b_y, 1.0); // point (b_x; b_y)
    glEnd();
}

void PLATF_RendererPresentScreen(void)
{
    glFlush();
}

void PLATF_RendererDeinit(void)
{

}
