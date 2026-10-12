#ifndef HISTOGRAM_H
#define HISTOGRAM_H

/*
 * Print the temperature histogram for a[0..n-1]. Values below 0 C are
 * placed in the first 0-to-5 C bin; values at least 100 C are placed in the
 * last 95-to-100 C bin. Requires a != NULL and n >= 1.
 */
void histogram_print(const float a[], int n);

#endif
