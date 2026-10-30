#include "store.h"
#include <assert.h>
#include <stdio.h>

struct walk_context {
    size_t count;
    record_t previous;
};

static void check_order(const record_t *record, void *context) {
    struct walk_context *walk = context;
    if (walk->count != 0)
        assert(record_compare(&walk->previous, record) < 0);
    walk->previous = *record;
    walk->count++;
}

int main(void) {
    record_t a = {.state = IDLE, .reading = {.timestamp = 20}};
    record_t b = {.state = IDLE, .reading = {.timestamp = 30}};
    assert(record_compare(&a, &b) < 0);
    assert(record_compare(&b, &a) > 0);
    assert(record_compare(&a, &a) == 0);
    b.state = RAMP;
    b.reading.timestamp = 20;
    assert(record_compare(&a, &b) < 0);
    b.reading.timestamp = 10;
    assert(record_compare(&a, &b) < 0); /* State takes priority. */

    store_t *store = store_create();
    assert(store != NULL);
    assert(store_count(store) == 0);
    assert(store_height(store) == 0);
    record_t out = {.status = 123};
    assert(store_find(store, IDLE, 0, &out) == 1);
    assert(out.status == 123);

    /* Reverse insertion exercises shifting and repeated array growth. */
    for (int i = 99; i >= 0; i--) {
        record_t record = {
            .reading = {.timestamp = i, .temp_c = 95.0f, .rh_pct = 10.0f},
            .state = (state_t)(i % 5),
            .status = (uint32_t)i
        };
        assert(store_insert(store, &record) == 0);
        assert(store_count(store) == (size_t)(100 - i));
    }
    assert(store_height(store) == 1); /* Temporary array convention. */
    for (int i = 0; i < 100; i++) {
        assert(store_find(store, (state_t)(i % 5), i, &out) == 0);
        assert(out.status == (uint32_t)i);
        assert(out.reading.temp_c == 95.0f);
        assert(out.reading.rh_pct == 10.0f);
    }
    out.status = 999;
    assert(store_insert(store, &out) == 1);
    assert(store_count(store) == 100);
    assert(store_find(store, FAULT, 99, &out) == 0);
    assert(out.status == 99);
    assert(store_find(store, IDLE, 101, &out) == 1);
    assert(out.status == 99);

    struct walk_context walk = {0};
    store_walk(store, check_order, &walk);
    assert(walk.count == 100);
    assert(store_insert(NULL, &a) == -1);
    assert(store_insert(store, NULL) == -1);
    assert(store_find(store, IDLE, 0, NULL) == -1);
    store_destroy(store);
    store_destroy(store_create());
    store_destroy(NULL);
    puts("Store checks passed");
    return 0;
}
