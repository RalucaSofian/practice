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
#include "logger.h"
#include "player_system.h"

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
double player_move_speed = 1.0; // player speed in m/sec

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

void PLAYER_Init(void)
{

}

void PLAYER_Update(double time_delta, ENTITY_entity* entity)
{
    INTYPES_key_code key_up    = KEY_W;
    INTYPES_key_code key_left  = KEY_A;
    INTYPES_key_code key_down  = KEY_S;
    INTYPES_key_code key_right = KEY_D;

    if ((NULL == entity) || (NULL == entity->player_info))
    {
        return;
    }

    // TEST
    double velocity = VEC2_len(entity->physics_info->velocity);
    LOGG_verbose("Player Vel: %f m/s", velocity);
    //TEST

    //! TODO: replace 2
    if (2 == entity->player_info->player_number)
    {
        key_up    = KEY_UP;
        key_left  = KEY_LEFT;
        key_down  = KEY_DOWN;
        key_right = KEY_RIGHT;
    }

    INTYPES_key_state up_state = INSYS_GetKeyState(key_up);
    if (KEY_STATE_PRESSED == up_state)
    {
        //! TODO: apply forces instead
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
