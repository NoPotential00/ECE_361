#include "stats.h"

#include <math.h>
#include <stdio.h>

static int near(float actual, float expected) {
    return fabsf(actual - expected) < 0.001f;
}

int main(void) {
    const float values[] = {-3.5f, 24.4f, 33.6f, 33.6f, 10.0f, 31.0f};
    int start = -2;
    int length;
    int failures = 0;

    if (!near(stats_min(values, 6), -3.5f))
        failures++;
    if (!near(stats_max(values, 6), 33.6f))
        failures++;
    if (!near(stats_max_tail(values, 6), stats_max(values, 6)))
        failures++;
    if (!near(stats_mean(values, 6), 21.516666f))
        failures++;
    length = stats_longest_run_above(values, 6, 30.0f, &start);
    if (length != 2 || start != 2)
        failures++;
    length = stats_longest_run_above(values, 6, 100.0f, &start);
    if (length != 0 || start != -1)
        failures++;

    if (failures != 0) {
        fprintf(stderr, "%d stats test(s) failed\n", failures);
        return 1;
    }
    puts("PASS  stats unit tests");
    return 0;
}
