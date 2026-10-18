#ifndef PTR_H
#define PTR_H

/**
 * @file ptr.h
 * @brief Operations on floats using pointers and pointer arithmetic.
 */

/**
 * @brief Exchange two floating-point values.
 * @param[in,out] a Pointer to the first value.
 * @param[in,out] b Pointer to the second value.
 * @pre Both pointers refer to valid, writable floats.
 * @return Nothing.
 */
void swap_float(float *a, float *b);

/**
 * @brief Find the minimum and maximum values in an array.
 * @param[in] a Pointer to the first of n readable floats.
 * @param[in] n Number of elements.
 * @param[out] min Destination for the minimum value.
 * @param[out] max Destination for the maximum value.
 * @pre For valid input, min and max point to distinct writable floats
 *      outside the input array.
 * @return 0 on success, or -1 if any pointer is NULL or n is less than 1.
 * @note Output values are unchanged when invalid input is rejected.
 */
int minmax(const float *a, int n, float *min, float *max);

/**
 * @brief Find the first value strictly greater than a threshold.
 * @param[in] a Pointer to the first of n readable floats.
 * @param[in] n Number of elements.
 * @param[in] threshold Value to compare against each element.
 * @return Pointer to the first matching element, or NULL if none matches,
 *         a is NULL, or n is less than 1.
 */
const float *find_above(const float *a, int n, float threshold);

/**
 * @brief Reverse an array in place.
 * @param[in,out] a Pointer to the first of n writable floats.
 * @param[in] n Number of elements.
 * @return Nothing.
 * @note Does nothing if a is NULL or n is less than 2.
 */
void reverse(float *a, int n);

#endif
