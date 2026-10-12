#ifndef STATS_H
#define STATS_H

/*
 * Statistics functions for an array of floating-point readings.
 *
 * Every function requires a != NULL and n >= 1 unless stated otherwise.
 * Functions read the array but do not modify it.
 */

/* Return the smallest value in a[0..n-1]. */
float stats_min(const float a[], int n);

/* Return the largest value in a[0..n-1] using ordinary recursion. */
float stats_max(const float a[], int n);

/* Return the arithmetic mean of the values in a[0..n-1]. */
float stats_mean(const float a[], int n);

/*
 * Return the length of the longest consecutive run in a[0..n-1] whose
 * values are strictly greater than threshold. If start_index is not NULL,
 * store the zero-based index of that run's first value there. Store -1 when
 * no value is greater than threshold. Ties keep the earliest run.
 */
int stats_longest_run_above(const float a[], int n, float threshold,
                            int *start_index);

/*
 * Return the largest value in a[0..n-1] using tail recursion. The recursive
 * helper carries the best value found so far and is private to stats.c.
 */
float stats_max_tail(const float a[], int n);

#endif
