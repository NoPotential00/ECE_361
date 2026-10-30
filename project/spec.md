# Kiln Controller Specifications
## States
1. IDLE
2. RAMP
    - Will heat to 95.0
3. SOAK
    - Holds 95.0 (elements on below 94.0 ) for 180 ticks
4. COOL
    - Lasts until the reading is below 10.0 then moves to IDLE
5. FAULT
    - Caused when reading exceeds 98.0

## Reactants
Kiln Controller reacts

## Storage (sorted-array milestone)
A record contains a timestamped sensor reading, the kiln state, and a
32-bit status word. The store owns copies of records in a dynamically
growing sorted array, hidden behind the opaque `store_t` interface.
Records are ordered by state (IDLE, RAMP, SOAK, COOL, FAULT), then timestamp.
An ordered walk therefore groups readings by state, with each group in
chronological order; it is not a global chronological history.

Duplicate state/timestamp keys are rejected without replacing the original.
Insert returns 0 on success, 1 for a duplicate, and -1 for an invalid argument
or allocation failure. Find copies the result to the caller and returns 0
when found, 1 when absent, and -1 for invalid arguments, leaving the output
unchanged on failure. Lookup uses binary search; insertion shifts later
records. Callbacks must not modify the store during traversal.

The array has no tree height. For this milestone, height returns 0 for an
empty store and 1 for a nonempty flat array. In week 8 it will report the
actual tree height in nodes (empty 0, leaf 1), with the same function signature.
