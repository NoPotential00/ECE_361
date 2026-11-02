#include <ctype.h>
#include <stdio.h>

#include "lock.h"

int main(void)
{
    state_t state = LOCKED;
    int input;

    while ((input = getchar()) != EOF) {
        char c = (char)input;
        event_t event;
        action_t action;
        state_t next;

        /* Whitespace separates test input characters and is not an event. */
        if (isspace((unsigned char)c)) {
            continue;
        }

        event = (event_t)lock_event(state, c);
        next = lock_step(state, event, &action);

        printf("%s %c %s -> %s %s\n",
               state_name(state), c, event_name(event),
               state_name(next), action_name(action));
        state = next;
    }

    printf("final: %s\n", state_name(state));
    return 0;
}
