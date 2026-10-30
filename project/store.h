#ifndef STORE_H
#define STORE_H
/* Store kiln readings and status records ordered by state and timestamp. */
#include <stddef.h>
#include "sensor.h"
#include "fsm.h"

typedef struct {
    reading_t reading;
    state_t state;
    uint32_t status;
} record_t;

typedef struct store store_t;

/* Records passed to callbacks are valid only during the call.
 * Callbacks must not modify or destroy the store being walked. */
typedef void (*store_visit_fn)(const record_t *record, void *context);

/* Compare non-NULL records by state, then timestamp; return -1, 0, or 1. */
int record_compare(const record_t *left, const record_t *right);
store_t *store_create(void); /* NULL on allocation failure. */
/* Copy a record into the store: 0 success, 1 duplicate, -1 error. */
int store_insert(store_t *store, const record_t *record);
/* Copy a matching record to out: 0 found, 1 absent, -1 invalid argument.
 * On failure, out is unchanged. */
int store_find(const store_t *store, state_t state, time_t timestamp,
               record_t *out);
void store_walk(const store_t *store, store_visit_fn visit, void *context);
size_t store_count(const store_t *store);
/* Temporary flat-array convention: 0 empty, 1 nonempty.
 * The tree implementation will return its actual height in nodes. */
size_t store_height(const store_t *store);
void store_destroy(store_t *store);

#endif
