#ifndef BITS_H
#define BITS_H

#include <stdint.h>

/*
 * Bit widths must be 1..32. For get_field and set_field, pos must be 0..31
 * and pos + width must be at most 32. Invalid calls return no output,
 * 0, the original word, and 0 respectively. set_field truncates value to
 * the requested width.
 */
void print_binary(uint32_t x, int width);

uint32_t get_field(uint32_t word, int pos, int width);

uint32_t set_field(uint32_t word, int pos, int width, uint32_t value);

int32_t sign_extend(uint32_t value, int width);

#endif