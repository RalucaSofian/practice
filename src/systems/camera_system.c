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
#include "conversions.h"
#include "camera_system.h"

/************************************************************************
* DEFINES
************************************************************************/

#define CAMERA_MARGIN       0.1 // meters from the edge when camera starts panning

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/

double camera_x = 0; // camera position on the X axis [m]
double camera_y = 0; // camera position on the Y axis [m]

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
    double window_width  = CONV_PixelsToMeters(PLATF_GetWindowWidth());
    double window_height = CONV_PixelsToMeters(PLATF_GetWindowHeight());

    // If player is at the left limit of the screen
    if (player->transform.position.x <= (camera_x + CAMERA_MARGIN))
    {
        // Move camera left by the no of meters the player crossed over the margin
        camera_x -= camera_x + CAMERA_MARGIN - player->transform.position.x;
    }

    // If player is at the right limit of the screen
    if ((player->transform.position.x + player->transform.width) >= (camera_x + window_width - CAMERA_MARGIN))
    {
        // Move camera right by the no of meters the player crossed over the margin
        camera_x += player->transform.position.x + player->transform.width - (camera_x + window_width - CAMERA_MARGIN);
    }

    // If player is at the bottom limit of the screen
    if (player->transform.position.y <= (camera_y + CAMERA_MARGIN))
    {
        // Move camera down by the no of meters the player crossed over the margin
        camera_y -= camera_y + CAMERA_MARGIN - player->transform.position.y;
    }

    // If player is at the top limit of the screen
    if ((player->transform.position.y + player->transform.height) >= (camera_y + window_height - CAMERA_MARGIN))
    {
        // Move camera up by the no of meters the player crossed over the margin
        camera_y += player->transform.position.y + player->transform.height - (camera_y + window_height - CAMERA_MARGIN);
    }
}

void CAMERA_Deinit(void)
{

}
