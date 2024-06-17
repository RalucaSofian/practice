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
#include <stdbool.h>

#include "input_types.h"
#include "vector.h"

/************************************************************************
* DATA TYPES
************************************************************************/

typedef struct _PLAYER_key_map
{
    INTYPES_key_code key_up;
    INTYPES_key_code key_left;
    INTYPES_key_code key_down;
    INTYPES_key_code key_right;
}PLAYER_key_map;

/*! @brief Structure of the player information
 */
typedef struct _PLAYER_info
{
    int            player_number;
    int            health;
    PLAYER_key_map key_map;
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
    double mass;         // [kg]
    vec2   force;        // [N]
    vec2   acceleration; // [m/s^2]
    vec2   velocity;     // [m/s]
    bool   is_on_ground; // true/false
}PHYS_physics_info;

/*! @brief Structure of the transforms applied to all entities
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
