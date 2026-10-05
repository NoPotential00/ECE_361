#include <stdint.h>
#include <stdio.h>
#include "bits.h"

void print_binary(uint32_t x, int width)
{
    if (width < 1 || width > 32)
    {
        return;
    }

    for (int i = width - 1; i >= 0; i--)
    {
        printf("%u", (x >> i) & 1u);
        if (i % 4 == 0 && i != 0)
        {
            printf(" ");
        }
    }
    printf("\n");
}

uint32_t get_field(uint32_t word, int pos, int width)
{
    if (pos < 0 || pos > 31 || width < 1 || width > 32 ||
        width > 32 - pos)
    {
        return 0u;
    }

    uint32_t mask = (width == 32) ? UINT32_MAX : ((1u << width) - 1u);
    return (word >> pos) & mask;
}

uint32_t set_field(uint32_t word, int pos, int width, uint32_t value)
{
    if (pos < 0 || pos > 31 || width < 1 || width > 32 ||
        width > 32 - pos)
    {
        return word;
    }

    uint32_t mask = (width == 32) ? UINT32_MAX : ((1u << width) - 1u);
    uint32_t field_mask = mask << pos;

    word &= ~field_mask;
    word |= (value & mask) << pos;
    return word;
}

int32_t sign_extend(uint32_t value, int width)
{
    if (width < 1 || width > 32)
    {
        return 0;
    }

    if (width == 32)
    {
        return (int32_t)value;
    }

    uint32_t mask = (1u << width) - 1u;
    value &= mask;

    if (value & (1u << (width - 1)))
    {
        value |= ~mask;
    }

    return (int32_t)value;
}