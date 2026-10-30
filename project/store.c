#include "store.h"
#include <stdlib.h>
#include <string.h>

struct store {
    record_t *records;
    size_t count;
    size_t capacity;
};

int record_compare(const record_t *left, const record_t *right) {
    if (left->state != right->state)
        return left->state < right->state ? -1 : 1;
    if (left->reading.timestamp != right->reading.timestamp)
        return left->reading.timestamp < right->reading.timestamp ? -1 : 1;
    return 0;
}

/* Find the first record whose key is at least key, or count if none. */
static size_t lower_bound(const store_t *store, const record_t *key) {
    size_t low = 0;
    size_t high = store->count;
    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (record_compare(&store->records[mid], key) < 0)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}

store_t *store_create(void) {
    return calloc(1, sizeof(store_t));
}

int store_insert(store_t *store, const record_t *record) {
    if (store == NULL || record == NULL)
        return -1;

    size_t index = lower_bound(store, record);
    if (index < store->count &&
        record_compare(&store->records[index], record) == 0)
        return 1;

    if (store->count == store->capacity) {
        size_t max_capacity = SIZE_MAX / sizeof(record_t);
        if (store->capacity >= max_capacity)
            return -1;
        size_t capacity = store->capacity == 0 ? 8 :
            (store->capacity > max_capacity / 2 ? max_capacity :
             store->capacity * 2);
        record_t *records = realloc(store->records, capacity * sizeof(*records));
        if (records == NULL)
            return -1;
        store->records = records;
        store->capacity = capacity;
    }

    memmove(&store->records[index + 1], &store->records[index],
            (store->count - index) * sizeof(*store->records));
    store->records[index] = *record;
    store->count++;
    return 0;
}

int store_find(const store_t *store, state_t state, time_t timestamp,
               record_t *out) {
    if (store == NULL || out == NULL)
        return -1;
    record_t key = {.state = state, .reading = {.timestamp = timestamp}};
    size_t index = lower_bound(store, &key);
    if (index == store->count || record_compare(&store->records[index], &key))
        return 1;
    *out = store->records[index];
    return 0;
}

void store_walk(const store_t *store, store_visit_fn visit, void *context) {
    if (store == NULL || visit == NULL)
        return;
    for (size_t i = 0; i < store->count; i++)
        visit(&store->records[i], context);
}

size_t store_count(const store_t *store) {
    return store == NULL ? 0 : store->count;
}

size_t store_height(const store_t *store) {
    return store_count(store) == 0 ? 0 : 1;
}

void store_destroy(store_t *store) {
    if (store != NULL) {
        free(store->records);
        free(store);
    }
}
