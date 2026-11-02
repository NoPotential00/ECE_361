#include <assert.h>
#include <stdio.h>

#include "../check.h"

static void copy_table(transition_t destination[N_STATES][N_EVENTS])
{
    for (state_t s = LOCKED; s < N_STATES; ++s) {
        for (event_t e = E_RIGHT; e < N_EVENTS; ++e) {
            destination[s][e] = lock_table[s][e];
        }
    }
}

static void test_valid_table(void)
{
    assert(fsm_check(lock_table, LOCKED, 0) == 0);
}

static void test_undefined_action(void)
{
    transition_t table[N_STATES][N_EVENTS];
    copy_table(table);
    table[LOCKED][E_RIGHT].action = A_UNDEFINED;
    assert(fsm_check((const transition_t (*)[N_EVENTS])table, LOCKED, 0) == 1);
}

static void test_invalid_next_state(void)
{
    transition_t table[N_STATES][N_EVENTS];
    copy_table(table);
    table[OPEN][E_RIGHT].next = (state_t)N_STATES;
    assert(fsm_check((const transition_t (*)[N_EVENTS])table, LOCKED, 0) == 1);
}

static void test_unreachable_state(void)
{
    transition_t table[N_STATES][N_EVENTS];
    copy_table(table);
    table[GOT2][E_RIGHT].next = GOT2;
    assert(fsm_check((const transition_t (*)[N_EVENTS])table, LOCKED, 0) == 1);
}

int main(void)
{
    test_valid_table();
    test_undefined_action();
    test_invalid_next_state();
    test_unreachable_state();
    puts("all checker tests passed");
    return 0;
}
