# Homework 4
## Rules
- No using dynamic memory allocation
 - e.g. malloc/calloc
- 'Struct tally' holds an array of entries, each a name and a count, kept sorted by name. A new name goes where it belongs; the later entries move up by one.
- **The tally copies each name safely:** check the length first, and never write past an array. No strcpy or strncpy without a length check.
- Makefile builds events with 'gcc -std=c11 -Wall -Wextra' and no warnings, 'make test' builds and runs the tests, 'make clean' removes what was build
 - The Makefile works on both Linux systems and Windows systems
- 'tally_t' is opaque and only 'tally.c' will completes the 'struct'

## How to build and test
```bash
make
make test
make clean
```

## Part 3: Opaque type
With a file containing only `#include "tally.h"` and the line `return t->n;`, the compiler reports:

```text
part3_probe.c:5:13: error: invalid use of incomplete typedef 'tally_t' {aka 'struct tally'}
    5 |     return t->n;
      |             ^~
```

The opaque type prevents code outside `tally.c` from seeing or directly accessing the fields inside `struct tally`. The header only declares that `tally_t` is a type, so client code can use pointers to it and call the public functions but cannot dereference the pointer or access members such as `n`. This is useful because it hides the implementation details, prevents callers from changing the tally state incorrectly, and allows the internal representation to change without requiring client code to change.

## Testing
tests/test_tally.c tests every function, at least: counting up; a name never added; an empty name; a name of exactly TALLY_LEN characters and one of TALLY_LEN + 1; NULL arguments; a full tally (a new name is refused, an existing one still counts); TALLY_MAX tallies, then one more (NULL); create after destroy; two tallies are independent; the print order. PASS or FAIL per test, a summary, and a nonzero exit status if any test fails.

## About
### tally.h/c
| Function | What it does |
| --- | --- |
| `tally_create` | a new, empty tally; `NULL` if `TALLY_MAX` tallies are already in use |
| `tally_destroy` | gives the tally back so that `tally_create` can hand it out again; `NULL` does nothing |
| `tally_add` | counts one more occurrence of a name and returns its new count; returns `-1` and changes nothing if the name is `NULL`, the name is empty or longer than `TALLY_LEN`, or the tally is full |
| `tally_count` | how often a name was added: `0` if never, or `-1` for `NULL` |
| `tally_size` | how many different names the tally holds: `0` for `NULL` |
| `tally_print` | one line per name, count, in alphabetical (`strcmp`) order |

### events.h/c
Reads standard input line by line with fgets, remove the newline, skips blank lines and lines that start with #, adds every other line to one tally, then prints the tally and one last line, names: N, lines skipped: S, where S counts the lines tally_add refused.
- **Example:** ./events < data/door.txt, with a data/door.txt of your own.

### Tests
tests every function, at least: counting up; a name never added; an empty name; a name of exactly TALLY_LEN characters and one of TALLY_LEN + 1; NULL arguments; a full tally (a new name is refused, an existing one still counts); TALLY_MAX tallies, then one more (NULL); create after destroy; two tallies are independent; the print order. PASS or FAIL per test, a summary, and a nonzero exit status if any test fails.
