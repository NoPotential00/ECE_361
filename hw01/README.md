### Homework 1
## Overview
This library provides four functions with unsigned 32-bit words and a decoder for a 16-bit thermostat status word. The library declares functions within bits.h and status.h while the implementations are in bits.c and status.c.

## How to Build
To run the tests, your current working directory must be within '.\hw01\'. Then you will be able to run the following command:

    make tests

This command will run a test that prints PASS or FAIL with a summary covering both ends of the valid width/position ranges, field setting and extraction, sign extension, thermostat example, and invalid-mode handling showing with a successful exit status of 0 and nonzero if one of the tests fails.

TO remove remaining object files, run:

    make clean

## Valid ranges of Inputs at Boundries
# print_binary(uint32_t x, int width)
This function will only accept a width between 1 and 32 otherwise it will not print anything.

# get_field(uint32_t word, int pos, int width)
This function will return the bits from __pos__ to __pos + width - 1__, shifting it down so that the lowest selected bit is bit 0. Invalid inputs will return 0.

__width__ will accept inputs from 1 to 32
__pos__ will accept inputs from 0 through 31
__pos + width__ can only be up to 32

# set_field(uint32_t word, int pos, int width, uint32_t value)
Returns a copy of word with bits __pos__ through __pos + width - 1__ replaced by the lowest width bits of value. Every bit outside the selected field is kept unchanged. Invalid inputs will return the word unchanged.

__width__ will accept inputs from 1 to 32
__pos + width__ can only be up to 32 
If __value__ has bits above the requested width, the upper bits are discarded.

# sign_extended(uint32_t value, int width)
This function will interpret the lowest width bits of value as a two's complement signed number and return the result as an int32_t. Invalid width returns 0.

__width__ will accepts inputs from 1 to 32
- Bits of value above width are ignored

## Invalid mode of staus_unpack()
__status_unpack__ will report mode values of 5, 6 or 7 as mode 0 as stated in the table and not ignores bit 7 as it is reserved so it does not report or reject it.