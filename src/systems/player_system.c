/*! @file player.c
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

#include "input_system.h"
#include "player_system.h"

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
double player_move_speed = 200.0; // player speed in pixels/sec

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

void PLAYER_Init(void)
{

}

void PLAYER_Update(double time_delta, ENTITY_entity* entity)
{
    INTYPES_key_code key_left  = KEY_A;
    INTYPES_key_code key_right = KEY_D;
    INTYPES_key_code key_up    = KEY_W;
    INTYPES_key_code key_down  = KEY_S;

    if ((NULL == entity) || (NULL == entity->player_info))
    {
        return;
    }
    //! TODO: replace 2
    if (2 == entity->player_info->player_number)
    {
        key_left  = KEY_LEFT;
        key_right = KEY_RIGHT;
        key_up    = KEY_UP;
        key_down  = KEY_DOWN;
    }

    INTYPES_key_state up_state = INSYS_GetKeyState(key_up);
    if (KEY_STATE_PRESSED == up_state)
    {
        entity->transform.position.y += (player_move_speed*time_delta);
    }

    INTYPES_key_state left_state = INSYS_GetKeyState(key_left);
    if (KEY_STATE_PRESSED == left_state)
    {
        entity->transform.position.x -= (player_move_speed*time_delta);
    }

    INTYPES_key_state down_state = INSYS_GetKeyState(key_down);
    if (KEY_STATE_PRESSED == down_state)
    {
        entity->transform.position.y -= (player_move_speed*time_delta);
    }

    INTYPES_key_state right_state = INSYS_GetKeyState(key_right);
    if (KEY_STATE_PRESSED == right_state)
    {
        entity->transform.position.x += (player_move_speed*time_delta);
    }
}

void PLAYER_Deinit(void)
{

}
