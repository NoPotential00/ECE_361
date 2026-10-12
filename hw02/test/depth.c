#include "stats.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int use_tail = 0;
    int n;
    float *values;
    float result;

    if (argc == 2) {
        n = atoi(argv[1]);
    } else if (argc == 3 && strcmp(argv[1], "tail") == 0) {
        use_tail = 1;
        n = atoi(argv[2]);
    } else {
        fprintf(stderr, "usage: %s [tail] n\n", argv[0]);
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }

    values = malloc((size_t)n * sizeof *values);
    if (values == NULL) {
        fprintf(stderr, "could not allocate %d values\n", n);
        return 1;
    }
    for (int i = 0; i < n; i++)
        values[i] = (float)i;

    result = use_tail ? stats_max_tail(values, n) : stats_max(values, n);
    printf("%s %d %.1f\n", use_tail ? "tail" : "ordinary", n, result);
    free(values);
    return 0;
}
