#include "ptr.h"
#include <stddef.h>
#include <stdio.h>

static int tests_run = 0;
static int tests_failed = 0;

static void check(const char *name, int passed) {
    tests_run++;
    if (!passed) {
        tests_failed++;
    }
    printf("%s: %s\n", passed ? "PASS" : "FAIL", name);
}

static int arrays_equal(const float *a, const float *b, int n) {
    for (const float *end = a + n; a < end; a++, b++) {
        if (*a != *b) {
            return 0;
        }
    }
    return 1;
}

static void test_swap_float(void) {
    float a = -2.0f;
    float b = 7.0f;
    swap_float(&a, &b);
    check("swap_float exchanges values", a == 7.0f && b == -2.0f);
    swap_float(&a, &a);
    check("swap_float with the same pointer", a == 7.0f);
}

static void test_minmax(void) {
    const float values[] = {3.0f, -2.0f, 8.0f, 1.0f, 8.0f};
    float min = 0.0f;
    float max = 0.0f;
    int result = minmax(values, 5, &min, &max);
    check("minmax on several values", result == 0 && min == -2.0f && max == 8.0f);

    result = minmax(values, 1, &min, &max);
    check("minmax on one value", result == 0 && min == 3.0f && max == 3.0f);

    min = 17.0f;
    max = 23.0f;
    result = minmax(values, 0, &min, &max);
    check("minmax n = 0 leaves outputs unchanged",
          result == -1 && min == 17.0f && max == 23.0f);
    result = minmax(values, -1, &min, &max);
    check("minmax negative n leaves outputs unchanged",
          result == -1 && min == 17.0f && max == 23.0f);
    result = minmax(NULL, 5, &min, &max);
    check("minmax NULL input leaves outputs unchanged",
          result == -1 && min == 17.0f && max == 23.0f);
    result = minmax(values, 5, NULL, &max);
    check("minmax NULL min leaves max unchanged", result == -1 && max == 23.0f);
    result = minmax(values, 5, &min, NULL);
    check("minmax NULL max leaves min unchanged", result == -1 && min == 17.0f);
}

static void test_find_above(void) {
    const float values[] = {1.0f, 4.0f, 7.0f, 6.0f};
    check("find_above returns first of two matches",
          find_above(values, 4, 4.0f) == values + 2);
    check("find_above with no matches", find_above(values, 4, 9.0f) == NULL);
    check("find_above excludes value equal to threshold",
          find_above(values, 4, 7.0f) == NULL);
    check("find_above with NULL input", find_above(NULL, 4, 0.0f) == NULL);
    check("find_above with n = 0", find_above(values, 0, 0.0f) == NULL);
}

static void test_reverse(void) {
    float even[] = {1.0f, 2.0f, 3.0f, 4.0f};
    const float even_expected[] = {4.0f, 3.0f, 2.0f, 1.0f};
    float odd[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    const float odd_expected[] = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    float single = 9.0f;

    reverse(even, 4);
    check("reverse even length", arrays_equal(even, even_expected, 4));
    reverse(odd, 5);
    check("reverse odd length", arrays_equal(odd, odd_expected, 5));
    reverse(&single, 1);
    check("reverse one element does nothing", single == 9.0f);
    reverse(even, 0);
    check("reverse n = 0 does nothing", arrays_equal(even, even_expected, 4));
    reverse(even, -1);
    check("reverse negative n does nothing", arrays_equal(even, even_expected, 4));
    reverse(NULL, 4);
    check("reverse NULL input returns safely", 1);
}

int main(void) {
    test_swap_float();
    test_minmax();
    test_find_above();
    test_reverse();
    printf("\nSummary: %d tests, %d passed, %d failed\n",
           tests_run, tests_run - tests_failed, tests_failed);
    return tests_failed != 0;
}
