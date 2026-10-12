#ifndef READING_H
#define READING_H

#include <stdio.h>

enum { READING_CAPACITY = 1000 };

typedef struct {
    int ticks[READING_CAPACITY];
    float temps[READING_CAPACITY];
    float hums[READING_CAPACITY];
    int count;
    int skipped;
} ReadingSet;

/*
 * Read readings from input into out. Blank lines and comments are ignored;
 * nonblank lines that do not contain three numbers increment skipped.
 * Return 0 on success and 1 if input or out is invalid. At most
 * READING_CAPACITY readings are stored; extra readings are ignored after a
 * warning is printed.
 */
int reading_read(FILE *input, ReadingSet *out);

#endif
