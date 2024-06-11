/*! @file collisions.c
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

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

double COLL_GetEntityOverlapX(ENTITY_entity* entity_one,
                              ENTITY_entity* entity_two)
{
    if ((NULL == entity_one) || (NULL == entity_two) ||
        (NULL == entity_one->physics_info) ||
        (NULL == entity_two->physics_info))
    {
        LOGG_warn("Received NULL parameter");
        return;
    }

    ENTITY_entity* obj_a = NULL;
    ENTITY_entity* obj_b = NULL;

    if (entity_one->transform.position.x <= entity_two->transform.position.x)
    {
        obj_a = entity_one;
        obj_b = entity_two;
    }
    else if (entity_two->transform.position.x < entity_one->transform.position.x)
    {
        obj_a = entity_two;
        obj_b = entity_one;
    }

    double overlap = (obj_a->transform.position.x + obj_a->transform.width) - obj_b->transform.position.x;
    if (overlap < 0.0)
    {
        LOGG_verbose("No overlap on X axis");
    }
    else
    {
        LOGG_verbose("Overlap on X axis = %f meters", overlap);
    }

    return overlap;
}

double COLL_GetEntityOverlapY(ENTITY_entity* entity_one,
                              ENTITY_entity* entity_two)
{
    if ((NULL == entity_one) || (NULL == entity_two) ||
        (NULL == entity_one->physics_info) ||
        (NULL == entity_two->physics_info))
    {
        LOGG_warn("Received NULL parameter");
        return;
    }

    ENTITY_entity* obj_a = NULL;
    ENTITY_entity* obj_b = NULL;

    if (entity_one->transform.position.y <= entity_two->transform.position.y)
    {
        obj_a = entity_one;
        obj_b = entity_two;
    }
    else if (entity_two->transform.position.y < entity_one->transform.position.y)
    {
        obj_a = entity_two;
        obj_b = entity_one;
    }

    double overlap = (obj_a->transform.position.y + obj_a->transform.height) - obj_b->transform.position.y;
    if (overlap < 0.0)
    {
        LOGG_verbose("No overlap on Y axis");
    }
    else
    {
        LOGG_verbose("Overlap on Y axis = %f meters", overlap);
    }

    return overlap;
}
