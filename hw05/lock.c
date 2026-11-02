#include "lock.h"

const transition_t lock_table[N_STATES][N_EVENTS] = {
    /*                 E_RIGHT             E_WRONG              E_CLOSE              E_TIMEOUT */
    /* LOCKED */ { { GOT1,  A_NONE   }, { LOCKED, A_BEEP   }, { LOCKED, A_NONE }, { LOCKED, A_NONE } },
    /* GOT1   */ { { GOT2,  A_NONE   }, { LOCKED, A_BEEP   }, { LOCKED, A_LOCK }, { LOCKED, A_NONE } },
    /* GOT2   */ { { OPEN,  A_UNLOCK }, { LOCKED, A_BEEP   }, { LOCKED, A_LOCK }, { LOCKED, A_NONE } },
    /* OPEN   */ { { OPEN,  A_NONE   }, { OPEN,   A_NONE   }, { LOCKED, A_LOCK }, { OPEN,   A_NONE } }
};

state_t lock_step(state_t s, event_t e, action_t *action)
{
    if (action != 0) {
        *action = A_UNDEFINED;
    }

    if (s < 0 || s >= N_STATES || e < 0 || e >= N_EVENTS) {
        return s;
    }

    if (action != 0) {
        *action = lock_table[s][e].action;
    }
    return lock_table[s][e].next;
}

int lock_event(state_t s, char c)
{
    if (c == 'c' || c == 'C') {
        return E_CLOSE;
    }
    if (c == 't' || c == 'T') {
        return E_TIMEOUT;
    }

    if (s == LOCKED && c == '3') {
        return E_RIGHT;
    }
    if (s == GOT1 && c == '1') {
        return E_RIGHT;
    }
    if (s == GOT2 && c == '4') {
        return E_RIGHT;
    }
    return E_WRONG;
}

const char *state_name(state_t s)
{
    static const char *const names[N_STATES] = {
        "LOCKED", "GOT1", "GOT2", "OPEN"
    };
    return (s >= 0 && s < N_STATES) ? names[s] : "UNKNOWN";
}

const char *event_name(event_t e)
{
    static const char *const names[N_EVENTS] = {
        "RIGHT", "WRONG", "CLOSE", "TIMEOUT"
    };
    return (e >= 0 && e < N_EVENTS) ? names[e] : "UNKNOWN";
}

const char *action_name(action_t a)
{
    static const char *const names[N_ACTIONS] = {
        "UNDEFINED", "NONE", "UNLOCK", "LOCK", "BEEP"
    };
    return (a >= 0 && a < N_ACTIONS) ? names[a] : "UNKNOWN";
}
