# Homework 3
## Rules
- **Pointer arithmetic only:** arrays don't use 'a[i]' and walk through indices by using pointer arithmetic only. Reverse uses two pointers that move toward each other and calls swap_float.
- **Const where function only reads:** used in the 'find_above()' function where the prototype is 'const float *find_above(const float *a, int n, float threshold);'.
- **A comment per function in ptr.h:** Doxygen comments are inside the header files for each function.

# How to build and test
## Commands needed to make, clean and run
```bash
make # Make
make clean # clean files
make test # Test program
```
Note: Make sure to clean before testing in case the program was previously compiled on an incompatible operating system as to prevent errors from occuring