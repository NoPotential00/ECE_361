#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>

#include "lock.h"

/**
 * Validate a finite-state-machine transition table.
 *
 * The checker reports one line for every undefined action, invalid next state,
 * or state that is unreachable from the supplied start state. Passing NULL
 * for @p out performs validation without printing the individual problems.
 *
 * @param table Transition table to validate.
 * @param start State from which reachability is evaluated.
 * @param[out] out Output stream for diagnostics, or NULL to suppress output.
 * @return Number of problems found. A valid table returns zero.
 */
int fsm_check(const transition_t table[N_STATES][N_EVENTS],
              state_t start,
              FILE *out);

#endif
