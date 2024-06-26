/*! @file conversions.h
 *
 *
 *
 *
 *
 */
#ifndef CONVERSIONS_H
#define CONVERSIONS_H

/************************************************************************
* INCLUDES
************************************************************************/
#include "entity_types.h"

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Convert a value from number of pixels to meters
 *  @param[in] pixels - no of pixels
 *  @return meters per no of pixels
 */
double CONV_PixelsToMeters(int pixels);

/*! @brief Convert a value from meters to number of pixels
 *  @param[in] meters - no of meters
 *  @return pixels per meter
 */
int CONV_MetersToPixels(double meters);

/*! @brief Convert a string representing the colour (written as 6 hexadecimal digits for RGB)
 *  into a renderable colour
 *  @param[in] hex_col - string representing the hex colour
 *  @return a render colour
 */
REND_colour CONV_HexToColour(char* hex_col);

#endif // CONVERSIONS_H
