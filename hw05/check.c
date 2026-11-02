#include <stdbool.h>

#include "check.h"

/** Print one checker diagnostic and count it as one problem. */
static int report(FILE *out, const char *message, const char *state,
                  const char *event)
{
    if (out != 0) {
        if (event != 0) {
            fprintf(out, "%s: %s/%s\n", message, state, event);
        } else {
            fprintf(out, "%s: %s\n", message, state);
        }
    }
    return 1;
}

int fsm_check(const transition_t table[N_STATES][N_EVENTS],
              state_t start,
              FILE *out)
{
    bool reachable[N_STATES] = { false };
    state_t queue[N_STATES];
    int head = 0;
    int tail = 0;
    int problems = 0;

    if (table == 0) {
        return report(out, "null transition table", "table", 0);
    }

    for (state_t s = LOCKED; s < N_STATES; ++s) {
        for (event_t e = E_RIGHT; e < N_EVENTS; ++e) {
            const transition_t entry = table[s][e];

            if (entry.action == A_UNDEFINED) {
                problems += report(out, "undefined action",
                                   state_name(s), event_name(e));
            }
            if (entry.next < 0 || entry.next >= N_STATES) {
                problems += report(out, "next state out of range",
                                   state_name(s), event_name(e));
            }
        }
    }

    if (start < 0 || start >= N_STATES) {
        return problems + report(out, "start state out of range", "start", 0);
    }

    reachable[start] = true;
    queue[tail++] = start;
    while (head < tail) {
        state_t s = queue[head++];

        for (event_t e = E_RIGHT; e < N_EVENTS; ++e) {
            state_t next = table[s][e].next;

            if (next >= 0 && next < N_STATES && !reachable[next]) {
                reachable[next] = true;
                queue[tail++] = next;
            }
        }
    }

    for (state_t s = LOCKED; s < N_STATES; ++s) {
        if (!reachable[s]) {
            problems += report(out, "unreachable state", state_name(s), 0);
        }
    }

    return problems;
}
