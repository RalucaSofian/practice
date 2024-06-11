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

#endif // CONVERSIONS_H
