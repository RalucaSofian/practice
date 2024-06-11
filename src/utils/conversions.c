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
