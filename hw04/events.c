#include "tally.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    tally_t *tally = tally_create();
    char line[TALLY_LEN + 2];
    int skipped = 0;
    int length;

    if (tally == NULL) {
        return 1;
    }

    while (fgets(line, sizeof line, stdin) != NULL) {
        int complete = strchr(line, '\n') != NULL;

        if (!complete) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Drain the remainder of an overlong input line. */
            }
        }

        length = (int)strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[--length] = '\0';
        }
        if (length > 0 && line[length - 1] == '\r') {
            line[--length] = '\0';
        }

        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        if (tally_add(tally, line) < 0) {
            ++skipped;
        }
    }

    tally_print(tally, stdout);
    printf("names: %d, lines skipped: %d\n", tally_size(tally), skipped);
    tally_destroy(tally);
    return 0;
}
