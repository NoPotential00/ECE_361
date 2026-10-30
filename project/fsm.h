#ifndef FSM_H
#define FSM_H
/* Manage kiln states, events, transitions, and control actions. */
typedef enum {
    IDLE,
    RAMP,
    SOAK,
    COOL,
    FAULT
} state_t;



#endif
