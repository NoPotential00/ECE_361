#ifndef TALLY_H
#define TALLY_H

/**
 * @file tally.h
 * @brief Public interface for the tally abstract data type.
 */

#include <stdio.h>

/** Maximum number of tallies that can exist at the same time. */
#define TALLY_MAX 4

/** Maximum number of different names one tally can hold. */
#define TALLY_NAMES 16

/** Maximum name length, excluding the terminating null character. */
#define TALLY_LEN 15

/** Opaque tally type whose representation is defined in tally.c. */
typedef struct tally tally_t;

/**
 * Create an empty tally.
 *
 * @return A pointer to a new tally, or NULL if all TALLY_MAX slots are in use.
 */
tally_t *tally_create(void);

/**
 * Destroy a tally and make its slot available for reuse.
 *
 * @param[in] t Tally to destroy. NULL is ignored.
 */
void    tally_destroy(tally_t *t);

/**
 * Add one occurrence of a name to a tally.
 *
 * Names are kept in strcmp order. A name is rejected if it is NULL, empty,
 * longer than TALLY_LEN, or if the tally already contains TALLY_NAMES names.
 *
 * @param[in,out] t Tally to update.
 * @param[in] name Name to add.
 * @return The updated count for the name, or -1 if the input is rejected.
 */
int     tally_add(tally_t *t, const char *name);

/**
 * Get the number of times a name occurs in a tally.
 *
 * @param[in] t Tally to search.
 * @param[in] name Name to find.
 * @return The count, 0 if the name is absent, or -1 if t or name is NULL.
 */
int     tally_count(const tally_t *t, const char *name);

/**
 * Get the number of different names in a tally.
 *
 * @param[in] t Tally to inspect.
 * @return The number of names, or 0 if t is NULL.
 */
int     tally_size(const tally_t *t);

/**
 * Print all names and counts in strcmp order.
 *
 * @param[in] t Tally to print.
 * @param[out] out Output stream. Nothing is printed if t or out is NULL.
 */
void    tally_print(const tally_t *t, FILE *out);

#endif