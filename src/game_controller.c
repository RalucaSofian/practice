/*! @file game_controller.c
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
#include "input_system.h"
#include "player_system.h"
#include "camera_system.h"
#include "render_system.h"
#include "physics_system.h"
#include "entity_types.h"
#include "game_controller.h"

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
int player_reset_handler_id; // handler ID for the player position Reset Event
int kb_quit_handler_id;      // handler ID for the KB Quit Event

// Internal colours defined in RGBA
REND_colour col_red        = {1.0, 0.0, 0.0, 1.0};
REND_colour col_green      = {0.0, 1.0, 0.0, 1.0};
REND_colour col_blue       = {0.0, 0.0, 1.0, 1.0};
REND_colour col_black      = {0.0, 0.0, 0.0, 1.0};
REND_colour col_white      = {1.0, 1.0, 1.0, 1.0};
REND_colour col_grey       = {0.5, 0.5, 0.5, 1.0};
REND_colour col_grey_light = {0.75, 0.75, 0.75, 1.0};
REND_colour col_grey_dark  = {0.25, 0.25, 0.25, 1.0};

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

/*! @brief Handler used for reacting to the ESC or CTRL+Q keys being pressed
 */
static void kb_quit_handler(EVSYS_kb_event* kb_event)
{
    // QUIT == ESC or CTRL+Q was pressed
    switch (kb_event->key_state)
    {
        case KEY_STATE_PRESSED:
        {
            if (KEY_ESCAPE == kb_event->key)
            {
                LOGG_info("ESC Pressed. Quitting");
                EVSYS_DispatchQuitEvent();
            }
            else if (KEY_Q == kb_event->key)
            {
                if (KEY_STATE_PRESSED == INSYS_GetKeyState(KEY_LEFT_CONTROL))
                {
                    LOGG_info("CTRL+Q Pressed. Quitting");
                    EVSYS_DispatchQuitEvent();
                }
            }
            break;
        }
        default:
            break;
    }
}

static void player_reset_handler(EVSYS_kb_event* kb_event)
{
    // Player Position Reset == R key was pressed
    if ((KEY_R == kb_event->key) && (KEY_STATE_PRESSED == kb_event->key_state))
    {
        ENTITY_entity* entity       = NULL;
        uint32_t       entity_count = ENTITY_GetNoOfEntities();
        for (int i = 0; i < entity_count; i++)
        {
            entity = ENTITY_GetEntityByIndex(i);
            if (NULL != entity->player_info)
            {
                LOGG_info("R Pressed. Resetting Player position");
                entity->transform.position.x = INITIAL_PLAYER_POS.x;
                entity->transform.position.y = INITIAL_PLAYER_POS.y;
                CAMERA_Init(0.0, 0.0);
            }
        }
    }
}

/************************************************************************
************************************************************************/

void GAMECTRL_Init(void)
{
    CAMERA_Init(0.0, 0.0);
    player_reset_handler_id = EVSYS_SubscribeKbEvent(player_reset_handler);
    kb_quit_handler_id = EVSYS_SubscribeKbEvent(kb_quit_handler);
    ENTITY_InitEntities(STARTING_NO_OF_ENTITIES);
    PLAYER_Init();

    const ENTITY_entity* floor = ENTITY_CreateStaticEntity(-10.0,
                                                           1.0,
                                                           100.0,
                                                           0.5,
                                                           col_black);
    LOGG_info("Floor Entity ID = %d", floor->id);

    const ENTITY_entity* static_entity2 = ENTITY_CreateStaticEntity(2.0,
                                                                    1.5,
                                                                    0.5,
                                                                    0.5,
                                                                    col_grey_dark);
    LOGG_info("Static Entity 2 ID = %d", static_entity2->id);

    const ENTITY_entity* static_entity3 = ENTITY_CreateStaticEntity(3.0,
                                                                    1.5,
                                                                    0.5,
                                                                    0.5,
                                                                    col_grey);
    LOGG_info("Static Entity 3 ID = %d", static_entity3->id);

    const ENTITY_entity* static_entity4 = ENTITY_CreateStaticEntity(4.0,
                                                                    1.5,
                                                                    0.5,
                                                                    0.5,
                                                                    col_grey_light);
    LOGG_info("Static Entity 4 ID = %d", static_entity4->id);

    const ENTITY_entity* static_entity5 = ENTITY_CreateStaticEntity(5.0,
                                                                    1.5,
                                                                    0.5,
                                                                    0.5,
                                                                    col_green);
    LOGG_info("Static Entity 5 ID = %d", static_entity5->id);

    ENTITY_entity* player_one = ENTITY_CreatePlayerEntity(INITIAL_PLAYER_POS.x,
                                                          INITIAL_PLAYER_POS.y,
                                                          0.5,
                                                          2.0,
                                                          col_grey,
                                                          1,
                                                          KEY_MAP_WASD);
    LOGG_info("Player One ID = %d", player_one->id);

    // ENTITY_entity* player_two = ENTITY_CreatePlayerEntity(10.0,
    //                                                       1.5,
    //                                                       0.5,
    //                                                       2.0,
    //                                                       col_red,
    //                                                       2);
    // LOGG_info("Player Two ID = %d", player_two->id);
}

void GAMECTRL_Update(double time_delta)
{
    ENTITY_entity* entity       = NULL;
    uint32_t       entity_count = ENTITY_GetNoOfEntities();
    for (int i = 0; i < entity_count; i++)
    {
        entity = ENTITY_GetEntityByIndex(i);
        if (NULL != entity->physics_info)
        {
            PHYS_ResetForce(entity);
        }

        if (NULL != entity->player_info)
        {
            PLAYER_Update(time_delta, entity);
        }

        if (NULL != entity->physics_info)
        {
            PHYS_ApplyDefaultForces(entity);
            PHYS_UpdateEntity(time_delta, entity);
        }

        if (NULL != entity->player_info)
        {
            CAMERA_Update(time_delta, entity);
        }
    }
}

void GAMECTRL_Render(void)
{
    RENDSYS_Begin(CAMERA_GetX(), CAMERA_GetY());
    RENDSYS_ClearScreenWithCol(col_white);

    // Render all entities, if they have Render Info
    ENTITY_entity* entity       = NULL;
    uint32_t       entity_count = ENTITY_GetNoOfEntities();
    for (int i = 0; i < entity_count; i++)
    {
        entity = ENTITY_GetEntityByIndex(i);
        if (NULL != entity->render_info)
        {
            RENDSYS_DrawEntity(entity);
            // DEBUG: Draw forces applied on to the player entity
            // if entity we've just drawn was a player
            if (NULL != entity->player_info)
            {
                // find entity center
                vec2 player_center;
                player_center.x = entity->transform.position.x + (entity->transform.width/2.0);
                player_center.y = entity->transform.position.y + (entity->transform.height/2.0);
                // draw force as a line
                // scale force down and translate it for drawing
                vec2 scaled_force = VEC2_scale(entity->physics_info->force, 1.0/2000.0);
                scaled_force = VEC2_add(player_center, scaled_force);
                RENDSYS_DrawLine(player_center,
                                 scaled_force,
                                 col_red);

                // draw veloocity as a line
                // scale velocity down and translate it for drawing
                vec2 scaled_velocity = VEC2_scale(entity->physics_info->velocity, 1.0/10.0);
                scaled_velocity = VEC2_add(player_center, scaled_velocity);
                RENDSYS_DrawLine(player_center,
                                 scaled_velocity,
                                 col_green);
            }
        }
    }

    RENDSYS_PresentScreen();
}

void GAMECTRL_Deinit(void)
{
    PLAYER_Deinit();
    ENTITY_DeinitEntities();
    EVSYS_UnsubscribeEvent(player_reset_handler_id);
    EVSYS_UnsubscribeEvent(kb_quit_handler_id);
}
