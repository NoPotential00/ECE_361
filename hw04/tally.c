#include "tally.h"

#include <string.h>

typedef struct {
    char name[TALLY_LEN + 1];
    int count;
} tally_entry_t;

struct tally {
    int in_use;
    int size;
    tally_entry_t entries[TALLY_NAMES];
};

static struct tally tallies[TALLY_MAX];

static int valid_name(const char *name) {
    size_t length;

    if (name == NULL || name[0] == '\0') {
        return 0;
    }

    length = strlen(name);
    return length <= TALLY_LEN;
}

static int find_name(const tally_t *t, const char *name) {
    int i;

    for (i = 0; i < t->size; ++i) {
        int comparison = strcmp(t->entries[i].name, name);
        if (comparison == 0) {
            return i;
        }
        if (comparison > 0) {
            break;
        }
    }
    return -1;
}

tally_t *tally_create(void) {
    int i;

    for (i = 0; i < TALLY_MAX; ++i) {
        if (!tallies[i].in_use) {
            tallies[i].in_use = 1;
            tallies[i].size = 0;
            return &tallies[i];
        }
    }
    return NULL;
}

void tally_destroy(tally_t *t) {
    if (t != NULL) {
        t->in_use = 0;
        t->size = 0;
    }
}

int tally_add(tally_t *t, const char *name) {
    int position;
    int i;

    if (t == NULL || !valid_name(name)) {
        return -1;
    }

    position = 0;
    while (position < t->size && strcmp(t->entries[position].name, name) < 0) {
        ++position;
    }

    if (position < t->size && strcmp(t->entries[position].name, name) == 0) {
        ++t->entries[position].count;
        return t->entries[position].count;
    }

    if (t->size == TALLY_NAMES) {
        return -1;
    }

    for (i = t->size; i > position; --i) {
        t->entries[i] = t->entries[i - 1];
    }

    strcpy(t->entries[position].name, name);
    t->entries[position].count = 1;
    ++t->size;
    return 1;
}

int tally_count(const tally_t *t, const char *name) {
    int position;

    if (t == NULL || name == NULL) {
        return -1;
    }

    position = find_name(t, name);
    return position < 0 ? 0 : t->entries[position].count;
}

int tally_size(const tally_t *t) {
    return t == NULL ? 0 : t->size;
}

void tally_print(const tally_t *t, FILE *out) {
    int i;

    if (t == NULL || out == NULL) {
        return;
    }

    for (i = 0; i < t->size; ++i) {
        fprintf(out, "%s: %d\n", t->entries[i].name, t->entries[i].count);
    }
}
