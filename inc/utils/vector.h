/*! @file vector.h
 *
 *
 *
 *
 *
 */
#ifndef VECTOR_H
#define VECTOR_H

/************************************************************************
* DATA TYPES
************************************************************************/

/*! @brief Structure of the 2-dimensional vectors
 */
typedef struct _vec2
{
    double x;
    double y;
}vec2;

/************************************************************************
* FUNCTION DECLARATIONS
************************************************************************/

/*! @brief Add two 2D vectors
 *  @param[in] a - first 2D vector
 *  @param[in] b - second 2D vector
 *  @return resultant vector after addition
 */
vec2 VEC2_add(vec2 a, vec2 b);

/*! @brief Subtract second 2D vector from the first 2D vector
 *  @param[in] a - first 2D vector
 *  @param[in] b - second 2D vector
 *  @return resultant vector after subtraction
 */
vec2 VEC2_sub(vec2 a, vec2 b);

/*! @brief Calculate the dot (scalar) product of two 2D vectors
 *  @param[in] a - first 2D vector
 *  @param[in] b - second 2D vector
 *  @return result of dot product
 */
double VEC2_dot(vec2 a, vec2 b);

/*! @brief Calculate the length (magnitude) of a 2D vector
 *  @param[in] a - 2D vector
 *  @return length of 2D vector
 */
double VEC2_len(vec2 a);

/*! @brief Normalize a 2D vector
 *  @param[in] a - 2D vector
 *  @return normalized (unit) 2D vector
 */
vec2 VEC2_normalize(vec2 a);

/*! @brief Scale a 2D vector by a scale factor
 *  @param[in] a - 2D vector
 *  @param[in] scale - scale factor
 *  @return result of vector scaling
 */
vec2 VEC2_scale(vec2 a, double scale);

#endif // VECTOR_H
