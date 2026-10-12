# Homework 2
## Rules
1. **No global variables.** The readings live in *main* and are passed to the functions that need them.
2. **One recursive maximum.** Replace *max_temp* witha  recursive function in *stats.c* that takes an array and its length, for example *float stats_max(const float a[], int n)*, and use it for the temperature and the humidity. The repeated loop disappears: each statisstic is computed by one function, called twice.
3. **Headers are contracts.** Every header has an include guard, declares only what other files call, and has a comment for each function: what it takes, what it returns, and what it assumes (for example, n $\geq$ 1).
4. **Helpers stay private.** A function used inside one *.c* file only is *static*. Name your public functions with the module as a prefix (*stats_max, histogram_print*) so that a reader knows where to look.
5. **Same output, byte for byte.** For every input file, your program prints exactly what *expected/* holds. Refactoring changes the structure, never the behavior.

## Requirements for Satisfactory
* In *hw02/:* make builds with no errors and no warnings, *make test* runs, all unit tests pass, the regression test finds no difference, and make *clean* works.
* No global variables, one recursive maximum, *static* helpers, and include guards.
* *README.md* and *AI_USAGE.md* are present and specific to your work.

## Optional: Bonus Problem
In Tuesday's lecture, the recursive maximum crashed at 200,000 values: every call that has not returned keeps a frame on the stack. This problem asks whether a different recursion can survive, and why.

1. Add `float stats_max_tail(const float a[], int n)` to your stats module: a recursive maximum whose helper carries the best value so far as a parameter, so that the recursive call is the last thing it does (a **tail call**). Test that it agrees with `stats_max`.
2. Write `test/depth.c`, which runs either maximum on n values given on the command line. Build it with `-O0` and with `-O2`.
3. For both versions and both settings, find the largest n that does not crash, to within about 10% (more than 20 million counts as "survives").
4. In `hw02/BONUS.md`: your four numbers in a table, with your computer and compiler, and an explanation in your own words. Why does one version survive at `-O2`? Why does it not at `-O0`? Why does `-O2` not save `stats_max`? What does this mean for a recursive function on a binary search tree?

The bonus earns one revision token when HW2 is Satisfactory and you answer the extra Shine question about your bonus well. AI tools are allowed, as for the rest of the homework, but the numbers must come from your own machine, and you must be able to explain them.

# How to Build and Test
## Commands needed to make, clean and run
```bash
make # Make
make clean # clean files
make test # Test program
```
Note: Make sure to clean before testing in case the program was previously compiled on an incompatible operating system as to prevent errors from occuring

# Module Diagram
![alt text](20261011_235719.jpg)