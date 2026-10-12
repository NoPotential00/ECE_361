#include "stats.h"
#include <stddef.h>

float stats_min(const float a[], int n) {
    float result = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < result)
            result = a[i];
    }
    return result;
}

float stats_max(const float a[], int n) {
    if (n == 1)
        return a[0];

    float rest = stats_max(a + 1, n - 1);
    return a[0] > rest ? a[0] : rest;
}

float stats_mean(const float a[], int n) {
    float total = 0.0f;
    for (int i = 0; i < n; i++)
        total += a[i];
    return total / n;
}

int stats_longest_run_above(const float a[], int n, float threshold,
                            int *start_index) {
    int run = 0;
    int best = 0;
    int current_start = 0;
    int best_start = -1;

    for (int i = 0; i < n; i++) {
        if (a[i] > threshold) {
            if (run == 0)
                current_start = i;
            run++;
            if (run > best) {
                best = run;
                best_start = current_start;
            }
        } else {
            run = 0;
        }
    }

    if (start_index != NULL)
        *start_index = best_start;
    return best;
}

static float stats_max_tail_helper(const float a[], int n, float best) {
    if (n == 0)
        return best;
    if (a[0] > best)
        best = a[0];
    return stats_max_tail_helper(a + 1, n - 1, best);
}

float stats_max_tail(const float a[], int n) {
    return stats_max_tail_helper(a + 1, n - 1, a[0]);
}
