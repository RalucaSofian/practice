/*! @file camera_system.c
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

#include "platform.h"
#include "entity_types.h"
#include "camera_system.h"

/************************************************************************
* DEFINES
************************************************************************/

#define CAMERA_MARGIN       50.0 // no of pixels from the edge when camera starts panning

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/

double camera_x = 0; // camera position on the X axis
double camera_y = 0; // camera position on the Y axis

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

void CAMERA_Init(double x, double y)
{
    camera_x = x;
    camera_y = y;
}

double CAMERA_GetX(void)
{
    return camera_x;
}

double CAMERA_GetY(void)
{
    return camera_y;
}

void CAMERA_Update(double time_delta, ENTITY_entity* player)
{
    int window_width = PLATF_GetWindowWidth();

    // If player is at the left limit of the screen
    if (player->transform.position.x <= (camera_x + CAMERA_MARGIN))
    {
        // Move camera left by the no of pixels the player crossed over the margin
        camera_x -= camera_x + CAMERA_MARGIN - player->transform.position.x;
    }

    // If player is at the right limit of the screen
    if ((player->transform.position.x + player->transform.width) >= (camera_x + window_width - CAMERA_MARGIN))
    {
        // Move camera right by the no of pixels the player crossed over the margin
        camera_x += player->transform.position.x + player->transform.width - (camera_x + window_width - CAMERA_MARGIN);
    }
}

void CAMERA_Deinit(void)
{

}
