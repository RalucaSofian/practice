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

#include "logger.h"
#include "vector.h"
#include "input_system.h"
#include "physics_system.h"
#include "player_system.h"


const PLAYER_key_map KEY_MAP_WASD   = {.key_up = KEY_W, .key_left = KEY_A, .key_down = KEY_S, .key_right = KEY_D};
const PLAYER_key_map KEY_MAP_ARROWS = {.key_up = KEY_UP, .key_left = KEY_LEFT, .key_down = KEY_DOWN, .key_right = KEY_RIGHT};
const vec2           INITIAL_PLAYER_POS = {.x = 1.0, .y = 2.0};

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
const double PLAYER_MOVEMENT_FORCE = 2000.0;
const double PLAYER_JUMP_FORCE     = 30000.0;

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

void PLAYER_Init(void)
{

}

void PLAYER_Update(double time_delta, ENTITY_entity* entity)
{
    if ((NULL == entity) || (NULL == entity->player_info))
    {
        return;
    }

    // TEST
    // double velocity = VEC2_len(entity->physics_info->velocity);
    // LOGG_verbose("Player Vel: %f m/s; is_on_ground: %d", velocity, entity->physics_info->is_on_ground);
    // TEST

    INTYPES_key_state up_state = INSYS_GetKeyState(entity->player_info->key_map.key_up);
    if ((KEY_STATE_PRESSED == up_state) && (true == entity->physics_info->is_on_ground))
    {
        PHYS_ApplyForce(entity, VEC2_scale(VEC2_UP, PLAYER_JUMP_FORCE));
    }

    INTYPES_key_state left_state = INSYS_GetKeyState(entity->player_info->key_map.key_left);
    if (KEY_STATE_PRESSED == left_state)
    {
        PHYS_ApplyForce(entity, VEC2_scale(VEC2_LEFT, PLAYER_MOVEMENT_FORCE));
    }

    INTYPES_key_state down_state = INSYS_GetKeyState(entity->player_info->key_map.key_down);
    if (KEY_STATE_PRESSED == down_state)
    {
        PHYS_ApplyForce(entity, VEC2_scale(VEC2_DOWN, PLAYER_MOVEMENT_FORCE));
    }

    INTYPES_key_state right_state = INSYS_GetKeyState(entity->player_info->key_map.key_right);
    if (KEY_STATE_PRESSED == right_state)
    {
        PHYS_ApplyForce(entity, VEC2_scale(VEC2_RIGHT, PLAYER_MOVEMENT_FORCE));
    }
}

void PLAYER_Deinit(void)
{

}
