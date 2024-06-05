/*! @file entity_types.h
 *
 *
 *
 *
 *
 */
#ifndef ENTITY_TYPES_H
#define ENTITY_TYPES_H

/************************************************************************
* INCLUDES
************************************************************************/
#include <stdint.h>

#include "vector.h"

/************************************************************************
* DATA TYPES
************************************************************************/

/*! @brief Structure of the player information
 */
typedef struct _PLAYER_info
{
    int player_number;
    int health;
}PLAYER_info;

/*! @brief Structure of the renderable colours
 */
typedef struct _REND_colour
{
    double red;
    double green;
    double blue;
    double alpha;
}REND_colour;

/*! @brief Structure of the renderable objects
 */
typedef struct _REND_render_info
{
    REND_colour colour;
}REND_render_info;

/*! @brief Structure of the objects with physics properties
 */
typedef struct _PHYS_physics_info
{
    double mass;
    vec2   force;
    vec2   acceleration;
    vec2   velocity;
}PHYS_physics_info; // entity sub-struct

/*! @brief Structure of the transforms applied to entities
 */
typedef struct _ENTITY_transform
{
    vec2   position;
    double width;
    double height;
}ENTITY_transform;

/*! @brief Structure of the entities present in the system
 */
typedef struct _ENTITY_entity
{
    // Entity properties
    uint32_t           id;
    ENTITY_transform   transform;
    // Components
    PLAYER_info*       player_info;
    REND_render_info*  render_info;
    PHYS_physics_info* physics_info;
}ENTITY_entity;

#endif // ENTITY_TYPES_H
