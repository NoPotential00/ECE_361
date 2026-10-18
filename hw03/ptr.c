#include "ptr.h"
#include <stddef.h>

void swap_float(float *a, float *b) {
    float t = *a;
    *a = *b;
    *b = t;
}

int minmax(const float *a, int n, float *min, float *max) {
    if (!a || !min || !max || n < 1) {
        return -1; // Error: invalid size or null pointer
    }

    *min = *max = *a;
    for (const float *p = a + 1; p < a + n; p++) {
        if (*p < *min) {
            *min = *p;
        }
        if (*p > *max) {
            *max = *p;
        }
    }
    return 0; // Success
}

const float *find_above(const float *a, int n, float threshold) {
    if (!a || n < 1) {
        return NULL; // Error: invalid size or null pointer
    }

    for (const float *p = a; p < a + n; p++) {
        if (*p > threshold) {
            return p;
        }
    }
    return NULL; // No element found above the threshold
}

void reverse(float *a, int n) {
    if (!a || n < 2) {
        return;
    }

    float *left = a;
    float *right = a + n - 1;
    while (left < right) {
        swap_float(left, right);
        left++;
        right--;
    }
}
