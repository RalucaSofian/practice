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

#include "physics_system.h"

/************************************************************************
* GLOBAL VARIABLES
************************************************************************/
const vec2 GRAVITY_ACC = {.x = 0.0, .y = -9.81};
const double FRICTION_COEF = 0.5 * 1.225 * 1.09 * 1.0; // 0.5 * air density * drag coef of a cube * cross sectional area of a unit cube

/************************************************************************
* FUNCTION DEFINITIONS
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
    // Fd = (-v/len(v)) * len(Fd); len(Fd) = FRICTION_COEF * len(v)^2
    vec2 velocity = entity->physics_info->velocity;
    double velocity_magnitude = VEC2_len(velocity);
    if (0 < velocity_magnitude)
    {
        double friction_magnitude = FRICTION_COEF * velocity_magnitude * velocity_magnitude;
        vec2 friction_dir = VEC2_scale(velocity, -1.0/velocity_magnitude);
        PHYS_ApplyForce(entity, VEC2_scale(friction_dir, friction_magnitude));
    }
}

void check_collisions(ENTITY_entity* entity)
{
    // check for overlap
        // utils: check_entity_overlap_x(entity1, entity2); ret meters overlap on x dir
        // utils: check_entity_overlap_y(entity1, entity2); ret meters overlap on y dir

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

    // call check_collisions

}

void PHYS_Deinit(void)
{

}
