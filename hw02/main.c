#include "histogram.h"
#include "reading.h"
#include "stats.h"

#include <stdio.h>
#include <stdlib.h>

static int parse_threshold(const char text[], float *threshold) {
    char *end;
    float value = strtof(text, &end);
    if (*end != '\0')
        return 1;
    *threshold = value;
    return 0;
}

int main(int argc, char *argv[]) {
    ReadingSet readings;
    float threshold = 30.0f;
    int best_start;
    int best;

    if (argc > 2) {
        fprintf(stderr, "usage: %s [threshold] < readings.txt\n", argv[0]);
        return 1;
    }
    if (argc == 2 && parse_threshold(argv[1], &threshold) != 0) {
        fprintf(stderr, "error: threshold '%s' is not a number\n", argv[1]);
        return 1;
    }
    if (reading_read(stdin, &readings) != 0)
        return 1;

    printf("readings: %d\n", readings.count);
    printf("skipped:  %d\n", readings.skipped);
    if (readings.count == 0) {
        printf("no readings, no summary\n");
        return 0;
    }

    printf("temperature: min %6.1f  max %6.1f  mean %6.2f C\n",
           stats_min(readings.temps, readings.count),
           stats_max(readings.temps, readings.count),
           stats_mean(readings.temps, readings.count));
    printf("humidity:    min %6.1f  max %6.1f  mean %6.2f %%RH\n",
           stats_min(readings.hums, readings.count),
           stats_max(readings.hums, readings.count),
           stats_mean(readings.hums, readings.count));

    best = stats_longest_run_above(readings.temps, readings.count,
                                   threshold, &best_start);
    if (best == 0) {
        printf("above %.1f C: never\n", threshold);
    } else {
        printf("above %.1f C: longest run %d readings, from tick %d to tick %d\n",
               threshold, best, readings.ticks[best_start],
               readings.ticks[best_start + best - 1]);
    }

    histogram_print(readings.temps, readings.count);
    return 0;
}
