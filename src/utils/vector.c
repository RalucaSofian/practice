/*! @file vector.c
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
#include <math.h>

#include "vector.h"

/************************************************************************
* CONSTANTS
************************************************************************/

const vec2 VEC2_UP    = {.x = 0.0, .y = 1.0};
const vec2 VEC2_DOWN  = {.x = 0.0, .y = -1.0};
const vec2 VEC2_LEFT  = {.x = -1.0, .y = 0.0};
const vec2 VEC2_RIGHT = {.x = 1.0, .y = 0.0};
const vec2 VEC2_ZERO  = {.x = 0.0, .y = 0.0};

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

vec2 VEC2_add(vec2 a, vec2 b)
{
    vec2 res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;

    return res;
}

vec2 VEC2_sub(vec2 a, vec2 b)
{
    vec2 res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;

    return res;
}

double VEC2_dot(vec2 a, vec2 b)
{
    double res;

    res = (a.x*b.x) + (a.y*b.y);

    return res;
}

double VEC2_len(vec2 a)
{
    double res;

    // res = sqrt(pow(a.x, 2) + pow(a.y, 2));
    res = sqrt((a.x*a.x)+(a.y*a.y));

    return res;
}

vec2 VEC2_normalize(vec2 a)
{
    vec2   res;
    double len = VEC2_len(a);

    res.x = a.x / len;
    res.y = a.y / len;

    return res;
}

vec2 VEC2_scale(vec2 a, double scale)
{
    vec2 res;

    res.x = a.x * scale;
    res.y = a.y * scale;

    return res;
}
