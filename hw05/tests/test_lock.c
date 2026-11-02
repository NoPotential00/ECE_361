#include <assert.h>
#include <stdio.h>

#include "../lock.h"

static void test_transition_table(void)
{
    static const transition_t expected[N_STATES][N_EVENTS] = {
        { { GOT1, A_NONE }, { LOCKED, A_BEEP }, { LOCKED, A_NONE }, { LOCKED, A_NONE } },
        { { GOT2, A_NONE }, { LOCKED, A_BEEP }, { LOCKED, A_LOCK }, { LOCKED, A_NONE } },
        { { OPEN, A_UNLOCK }, { LOCKED, A_BEEP }, { LOCKED, A_LOCK }, { LOCKED, A_NONE } },
        { { OPEN, A_NONE }, { OPEN, A_NONE }, { LOCKED, A_LOCK }, { OPEN, A_NONE } }
    };

    for (state_t s = LOCKED; s < N_STATES; ++s) {
        for (event_t e = E_RIGHT; e < N_EVENTS; ++e) {
            assert(lock_table[s][e].next == expected[s][e].next);
            assert(lock_table[s][e].action == expected[s][e].action);
        }
    }
}

static void test_event_translation(void)
{
    assert(lock_event(LOCKED, '3') == E_RIGHT);
    assert(lock_event(GOT1, '1') == E_RIGHT);
    assert(lock_event(GOT2, '4') == E_RIGHT);

    assert(lock_event(LOCKED, '1') == E_WRONG);
    assert(lock_event(GOT1, '4') == E_WRONG);
    assert(lock_event(GOT2, '3') == E_WRONG);
    assert(lock_event(OPEN, '3') == E_WRONG);

    assert(lock_event(LOCKED, 'c') == E_CLOSE);
    assert(lock_event(GOT1, 't') == E_TIMEOUT);
}

static void test_lock_step(void)
{
    action_t action;
    state_t state = LOCKED;

    state = lock_step(state, lock_event(state, '3'), &action);
    assert(state == GOT1 && action == A_NONE);
    state = lock_step(state, lock_event(state, '1'), &action);
    assert(state == GOT2 && action == A_NONE);
    state = lock_step(state, lock_event(state, '4'), &action);
    assert(state == OPEN && action == A_UNLOCK);
    state = lock_step(state, lock_event(state, 'c'), &action);
    assert(state == LOCKED && action == A_LOCK);
}

static void test_reset_paths(void)
{
    action_t action;
    state_t state = GOT1;

    state = lock_step(state, E_WRONG, &action);
    assert(state == LOCKED && action == A_BEEP);

    state = GOT2;
    state = lock_step(state, E_TIMEOUT, &action);
    assert(state == LOCKED && action == A_NONE);

    state = OPEN;
    state = lock_step(state, E_CLOSE, &action);
    assert(state == LOCKED && action == A_LOCK);
}

static void test_names(void)
{
    assert(state_name(LOCKED)[0] == 'L');
    assert(event_name(E_RIGHT)[0] == 'R');
    assert(action_name(A_UNLOCK)[0] == 'U');
}

int main(void)
{
    test_transition_table();
    test_event_translation();
    test_lock_step();
    test_reset_paths();
    test_names();
    puts("all lock tests passed");
    return 0;
}
