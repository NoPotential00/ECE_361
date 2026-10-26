#include "tally.h"

#include <stdio.h>
#include <string.h>

static int failures;

static void check(int condition, const char *message) {
    if (!condition) {
        fprintf(stderr, "FAIL: %s\n", message);
        ++failures;
    }
}

int main(void) {
    tally_t *t = tally_create();
    char long_name[TALLY_LEN + 2] = "1234567890123456";
    FILE *output;
    char printed[128];

    check(t != NULL, "create returns a tally");
    check(tally_size(t) == 0, "new tally is empty");
    check(tally_add(t, "pear") == 1, "first add returns one");
    check(tally_add(t, "pear") == 2, "repeated add increments");
    check(tally_add(t, "apple") == 1, "second name can be added");
    check(tally_count(t, "pear") == 2, "count finds existing name");
    check(tally_count(t, "missing") == 0, "count misses as zero");
    check(tally_size(t) == 2, "size counts distinct names");
    check(tally_add(t, NULL) == -1, "NULL name is rejected");
    check(tally_add(t, "") == -1, "empty name is rejected");
    check(tally_add(t, long_name) == -1, "overlong name is rejected");

    output = tmpfile();
    check(output != NULL, "temporary output can be opened");
    if (output != NULL) {
        tally_print(t, output);
        rewind(output);
        printed[0] = '\0';
        fgets(printed, sizeof printed, output);
        check(strcmp(printed, "apple: 1\n") == 0, "print is sorted");
        fclose(output);
    }

    tally_destroy(t);
    check(tally_create() == t, "destroyed slot can be reused");
    check(tally_count(NULL, "x") == -1, "NULL tally count is rejected");
    check(tally_size(NULL) == 0, "NULL tally size is zero");

    if (failures == 0) {
        puts("PASS");
    }
    return failures == 0 ? 0 : 1;
}
