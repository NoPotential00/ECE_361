#include "histogram.h"

#include <stdio.h>

#define HISTOGRAM_BINS 20
#define BIN_WIDTH 5.0f

void histogram_print(const float a[], int n) {
    int bins[HISTOGRAM_BINS] = {0};

    for (int i = 0; i < n; i++) {
        int bin = (int)(a[i] / BIN_WIDTH);
        if (a[i] < 0.0f)
            bin = 0;
        if (bin >= HISTOGRAM_BINS)
            bin = HISTOGRAM_BINS - 1;
        bins[bin]++;
    }

    printf("histogram:\n");
    for (int bin = 0; bin < HISTOGRAM_BINS; bin++) {
        if (bins[bin] == 0)
            continue;
        printf("  %5.1f to %5.1f C | ", bin * BIN_WIDTH,
               (bin + 1) * BIN_WIDTH);
        for (int i = 0; i < bins[bin]; i++)
            putchar('*');
        printf(" %d\n", bins[bin]);
    }
}
