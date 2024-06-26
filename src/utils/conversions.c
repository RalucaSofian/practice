/*! @file conversions.c
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
#include <string.h>

#include "entity_types.h"
#include "conversions.h"

/************************************************************************
* DEFINES
************************************************************************/
#define PX_PER_METER    50

/************************************************************************
* FUNCTION DEFINITIONS
************************************************************************/

double CONV_PixelsToMeters(int pixels)
{
    return ((double)pixels / PX_PER_METER);
}

int CONV_MetersToPixels(double meters)
{
    return (int)(meters * PX_PER_METER);
}

REND_colour CONV_HexToColour(char* hex_col)
{
    REND_colour colour = {0.0, 0.0, 0.0, 1.0}; // black

    if ((NULL == hex_col) || (strlen(hex_col) < 6))
    {
        return colour;
    }

    // Split input: 2 hex chars for each colour component
    char red_comp[3]   = {hex_col[0], hex_col[1], '\0'};
    char green_comp[3] = {hex_col[2], hex_col[3], '\0'};
    char blue_comp[3]  = {hex_col[4], hex_col[5], '\0'};

    unsigned int red;
    unsigned int green;
    unsigned int blue;

    sscanf(red_comp, "%x", &red);
    colour.red = (double)red/255;

    sscanf(green_comp, "%x", &green);
    colour.green = (double)green/255;

    sscanf(blue_comp, "%x", &blue);
    colour.blue = (double)blue/255;

    return colour;
}
