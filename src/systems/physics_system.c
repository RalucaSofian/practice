/*! @file physics_system.c
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
#include "collisions.h"
#include "entity_system.h"
#include "input_system.h"
#include "physics_system.h"

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
const vec2   GRAVITY_ACC          = {.x = 0.0, .y = -9.81}; // gravity acceleration
const double AIR_FRICTION_COEF    = 0.5 * 1.225 * 1.09 * 1.0 * 20; // 0.5 * air density * drag coef of a cube * cross sectional area of a unit cube * k
const double GROUND_FRICTION_COEF = 1.0;

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

/*! @brief Internal function used for checking for entity collisions
 *  @param[in] entity - entity for which we need to check for collisions
 */
static void check_collisions(ENTITY_entity* entity)
{
    entity->physics_info->is_on_ground = false;
    uint32_t entity_no = ENTITY_GetNoOfEntities();
    for (int i = 0; i < entity_no; i++)
    {
        ENTITY_entity* other_entity = ENTITY_GetEntityByIndex(i);
        if (entity->id != other_entity->id)
        {
            double overlap_x = COLL_GetEntityOverlapX(entity, other_entity);
            double overlap_y = COLL_GetEntityOverlapY(entity, other_entity);
            if ((overlap_x >= 0.0) && (overlap_y >= 0.0))
            {
                // LOGG_info("Collision detected. Entity IDs: %d and %d; Overlaps: X = %f Y = %f", entity->id, other_entity->id, overlap_x, overlap_y);
                if (overlap_x < overlap_y) // if horizontal overlap is smallest
                {
                    if (entity->physics_info->velocity.x > 0.0) // if entity was moving right
                    {
                        entity->transform.position.x -= overlap_x; // move entity left by the overlap amount
                    }
                    else // if entity was moving left
                    {
                        entity->transform.position.x += overlap_x; // move entity right by the overlap amount
                    }
                    entity->physics_info->velocity.x = 0.0; // stop entity movement on the horizontal axis
                }
                else
                {
                    if (entity->physics_info->velocity.y > 0.0)
                    {
                        entity->transform.position.y -= overlap_y;
                    }
                    else
                    {
                        entity->transform.position.y += overlap_y;
                        entity->physics_info->is_on_ground = true;
                    }
                    entity->physics_info->velocity.y = 0.0;
                }
            }
        }
    }
}


/************************************************************************
************************************************************************/

void PHYS_Init(void)
{

}

void PHYS_ResetForce(ENTITY_entity* entity)
{
    if ((NULL != entity) && (NULL != entity->physics_info))
    {
        entity->physics_info->force = VEC2_ZERO;
    }
}

void PHYS_ApplyForce(ENTITY_entity* entity, vec2 force)
{
    if ((NULL != entity) && (NULL != entity->physics_info))
    {
        entity->physics_info->force = VEC2_add(entity->physics_info->force, force);
    }
}

void PHYS_ApplyDefaultForces(ENTITY_entity* entity)
{
    // Apply gravity
    PHYS_ApplyForce(entity, VEC2_scale(GRAVITY_ACC, entity->physics_info->mass));

    // Apply air friction
    // Fd = (-v/len(v)) * len(Fd); len(Fd) = AIR_FRICTION_COEF * len(v)^2
    vec2 velocity = entity->physics_info->velocity;
    double velocity_magnitude = VEC2_len(velocity);
    if (velocity_magnitude > 0)
    {
        vec2 friction_dir = VEC2_scale(velocity, -1.0/velocity_magnitude);
        double friction_magnitude = AIR_FRICTION_COEF * velocity_magnitude * velocity_magnitude;
        PHYS_ApplyForce(entity, VEC2_scale(friction_dir, friction_magnitude));

        if (true == entity->physics_info->is_on_ground)
        {
            // if speed is negligible
            if ((entity->physics_info->velocity.x >= -0.1) &&
                (entity->physics_info->velocity.x <= 0.1))
            {
                entity->physics_info->velocity.x = 0.0;
            }
            else // if entity is moving
            {
                // only apply friction if it does NOT conflict with player input
                INTYPES_key_state left_state  = INSYS_GetKeyState(entity->player_info->key_map.key_left);
                INTYPES_key_state right_state = INSYS_GetKeyState(entity->player_info->key_map.key_right);

                if (((friction_dir.x > 0) && (KEY_STATE_PRESSED != left_state)) ||
                    ((friction_dir.x < 0) && (KEY_STATE_PRESSED != right_state)))
                {
                    friction_magnitude = GROUND_FRICTION_COEF * entity->physics_info->mass * VEC2_len(GRAVITY_ACC);
                    PHYS_ApplyForce(entity, VEC2_scale(friction_dir, friction_magnitude));
                }
            }
        }
    }
}

void PHYS_UpdateEntity(double time_delta, ENTITY_entity* entity)
{
    if ((NULL == entity) || (NULL == entity->physics_info))
    {
        return;
    }

    // a = F/m
    entity->physics_info->acceleration = VEC2_scale(entity->physics_info->force, 1/(entity->physics_info->mass));

   // v = v + a*dt
    entity->physics_info->velocity = VEC2_add(entity->physics_info->velocity,
                                              VEC2_scale(entity->physics_info->acceleration, time_delta));

    // pos = pos + v*dt
    entity->transform.position = VEC2_add(entity->transform.position,
                                          VEC2_scale(entity->physics_info->velocity, time_delta));

    check_collisions(entity);

}

void PHYS_Deinit(void)
{

}
