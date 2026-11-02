# Bonus: FSM table checker

## Implementation

The bonus is implemented by [`check.c`](./check.c) and [`check.h`](./check.h):

```c
int fsm_check(const transition_t table[N_STATES][N_EVENTS],
              state_t start,
              FILE *out);
```

`fsm_check` examines a transition table starting from `start`. It prints one
line for every problem it finds and returns the total number of problems.

The checker detects the three required table defects:

1. An entry has `A_UNDEFINED` as its action.
2. An entry points to a state outside `[0, N_STATES)`.
3. A state cannot be reached from the supplied start state.

A valid copy of the lock table returns `0`.

## Why each defect matters

### Undefined action

An `A_UNDEFINED` entry means the FSM has not specified what physical action
should happen for a valid state/event pair. For a lock, that could leave the
door unlocked, fail to beep after a wrong digit, or fail to relock the door.

### Invalid next state

The next state must be one of `LOCKED`, `GOT1`, `GOT2`, or `OPEN`. An invalid
value can cause an array access outside the transition table or make the lock
enter a state that the program does not understand. This is both a correctness
and memory-safety bug.

### Unreachable state

An unreachable state can never be entered during normal operation. For this
lock, an unreachable `OPEN` state would mean that no valid combination could
unlock the door. An unreachable intermediate state would mean part of the
combination sequence is dead code.

## Tests and Make target

[`tests/test_check.c`](./tests/test_check.c) checks a valid table and creates
one broken table for each required defect. Run the bonus tests with:

```text
make bonus
```

On Windows with MinGW, use `mingw32-make bonus`.

