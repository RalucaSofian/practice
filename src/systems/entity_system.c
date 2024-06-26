/*! @file entity_system.c
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
#include <stdlib.h> // malloc; free...

#include "logger.h"
#include "entity_system.h"

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/

ENTITY_entity** entities;                // array of pointers, of type 'entity'
uint32_t        entity_count    = 0;     // index of entities [0; max]
uint32_t        last_entity_id  = 0;     // ID of last added entity [1; max]
uint32_t        entity_capacity = 0;

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

/*! @brief Internal function used for checking the entity capacity and
 *         updating it if necessary
 */
static void check_entity_capacity(void)
{
    LOGG_info("entity_count = %d; entity_capacity = %d", entity_count, entity_capacity);

    // If we are at 75% used capacity, double entity capacity
    if (entity_count > (0.75*entity_capacity))
    {
        entities = (ENTITY_entity**)realloc(entities, 2 * entity_capacity * sizeof(ENTITY_entity*));
        entity_capacity = 2 * entity_capacity;
        LOGG_info("Expanded: entity_count = %d; entity_capacity = %d", entity_count, entity_capacity);
    }
}


/************************************************************************
************************************************************************/

void ENTITY_InitEntities(uint32_t no_of_entities)
{
    entities = (ENTITY_entity**)calloc(no_of_entities, sizeof(ENTITY_entity*));
    entity_capacity = no_of_entities; // initial capacity
}

uint32_t ENTITY_GetNoOfEntities(void)
{
    return entity_count;
}

ENTITY_entity* ENTITY_CreateStaticEntity(double x, double y,
                                         double width, double height,
                                         REND_colour colour)
{
    // Allocate memory for the non-moving entity
    entities[entity_count] = (ENTITY_entity*)malloc(sizeof(ENTITY_entity));

    ENTITY_entity* new_static_entity = entities[entity_count];

    new_static_entity->id = ++last_entity_id;

    new_static_entity->transform.position.x = x;
    new_static_entity->transform.position.y = y;
    new_static_entity->transform.width      = width;
    new_static_entity->transform.height     = height;

    new_static_entity->render_info = (REND_render_info*)malloc(sizeof(REND_render_info));
    new_static_entity->render_info->colour = colour;

    new_static_entity->player_info  = NULL;
    new_static_entity->physics_info = NULL;

    entity_count++;

    // Check how much space we have left
    check_entity_capacity();

    return new_static_entity;
}

ENTITY_entity* ENTITY_CreatePlayerEntity(double x, double y,
                                         double width, double height,
                                         REND_colour colour,
                                         int player_number, PLAYER_key_map key_map)
{
    // Start from a non-moving entity
    ENTITY_entity* player_entity = ENTITY_CreateStaticEntity(x, y, width, height, colour);

    player_entity->player_info = (PLAYER_info*)malloc(sizeof(PLAYER_info));
    player_entity->player_info->player_number = player_number;
    player_entity->player_info->key_map       = key_map;

    player_entity->physics_info = (PHYS_physics_info*)malloc(sizeof(PHYS_physics_info));
    player_entity->physics_info->mass         = 50;
    player_entity->physics_info->force        = VEC2_ZERO;
    player_entity->physics_info->acceleration = VEC2_ZERO;
    player_entity->physics_info->velocity     = VEC2_ZERO;
    player_entity->physics_info->is_on_ground = false;

    return player_entity;
}

// const entity* create_dynamic_entity(double x, double y,
//                                     double width, double height,
//                                     double mass, renderer_colour colour)
// {

// }

ENTITY_entity* ENTITY_GetEntityByIndex(uint32_t entity_index)
{
    // LOGG_verbose("Requested Index = %d; Entity Capacity = %d; No. of Entities = %d", entity_index, entity_capacity, entity_count);
    return entities[entity_index];
}

ENTITY_entity* ENTITY_GetEntityById(uint32_t entity_id)
{
    ENTITY_entity* entity_by_id = NULL;

    for (int i = 0; i < entity_count; i++)
    {
        if (entity_id == entities[i]->id)
        {
            entity_by_id = entities[i];
        }
    }

    return entity_by_id;
}

void ENTITY_DestroyEntityById(uint32_t id)
{
    for (int i = 0; i < entity_count; i++)
    {
        if (id == entities[i]->id)
        {
            free(entities[i]->player_info);
            free(entities[i]->render_info);
            free(entities[i]->physics_info);
            free(entities[i]);
            for(int j = i; j < entity_count-1; j++)
            {
                entities[j] = entities[j+1];
            }
            entities[entity_count-1] = NULL;
            break;
        }
    }

    entity_count--;
}

void ENTITY_DeinitEntities(void)
{
    for (int i = 0; i < entity_count; i++)
    {
        if (NULL != entities[i]->player_info)
        {
            free(entities[i]->player_info);
        }

        if (NULL != entities[i]->render_info)
        {
            free(entities[i]->render_info);
        }

        if (NULL != entities[i]->physics_info)
        {
            free(entities[i]->physics_info);
        }

        if (NULL != entities[i])
        {
            free(entities[i]);
        }
    }

    if (NULL != entities)
    {
        free(entities);
    }
}
