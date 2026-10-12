#include "reading.h"

#include <stdio.h>

#define LINE_LENGTH 128

int reading_read(FILE *input, ReadingSet *out) {
    char line[LINE_LENGTH];

    if (input == NULL || out == NULL)
        return 1;

    out->count = 0;
    out->skipped = 0;

    while (fgets(line, sizeof line, input) != NULL) {
        int i = 0;
        int tick;
        float temp;
        float hum;

        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] == '\n' || line[i] == '\0' || line[i] == '#')
            continue;
        if (out->count == READING_CAPACITY) {
            fprintf(stderr,
                    "warning: more than %d readings, the rest are ignored\n",
                    READING_CAPACITY);
            break;
        }
        if (sscanf(line, "%d %f %f", &tick, &temp, &hum) == 3) {
            out->ticks[out->count] = tick;
            out->temps[out->count] = temp;
            out->hums[out->count] = hum;
            out->count++;
        } else {
            out->skipped++;
        }
    }

    return ferror(input) ? 1 : 0;
}
