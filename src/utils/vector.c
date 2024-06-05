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
