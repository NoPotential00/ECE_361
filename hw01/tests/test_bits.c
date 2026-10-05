#include <stdio.h>
#include <stdint.h>
#include <string.h>

#if defined(_WIN32)
#include <io.h>
#define DUP _dup
#define DUP2 _dup2
#define CLOSE _close
#else
#include <unistd.h>
#define DUP dup
#define DUP2 dup2
#define CLOSE close
#endif

#include "../bits.h"
#include "../status.h"

static int failures = 0;
static int total = 0;

#define CHECK(name, condition)                                                  \
    do                                                                          \
    {                                                                           \
        total++;                                                                \
        if (condition)                                                          \
        {                                                                       \
            printf("PASS: %s\n", name);                                         \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            printf("FAIL: %s\n", name);                                         \
            failures++;                                                         \
        }                                                                       \
    } while (0)

static void print_binary_example(void)
{
    print_binary(0x2Cu, 8);
}

static void test_print_binary(void)
{
    FILE *capture = tmpfile();
    char buffer[64];
    int saved_fd = -1;

    if (capture == NULL)
    {
        CHECK("print_binary capture", 0);
        return;
    }

    saved_fd = DUP(fileno(stdout));
    if (saved_fd < 0)
    {
        CHECK("print_binary capture", 0);
        fclose(capture);
        return;
    }

    fflush(stdout);
    if (DUP2(fileno(capture), fileno(stdout)) < 0)
    {
        CHECK("print_binary capture", 0);
        CLOSE(saved_fd);
        fclose(capture);
        return;
    }

    print_binary_example();
    fflush(stdout);
    DUP2(saved_fd, fileno(stdout));
    CLOSE(saved_fd);

    rewind(capture);
    if (fgets(buffer, sizeof(buffer), capture) == NULL)
    {
        CHECK("print_binary width 8", 0);
        fclose(capture);
        return;
    }

    CHECK("print_binary width 8", strcmp(buffer, "0010 1100\n") == 0);
    fclose(capture);
}

static void test_get_field(void)
{
    CHECK("get_field width 1", get_field(0x1u, 0, 1) == 1u);
    CHECK("get_field pos 31 width 1", get_field(0x80000000u, 31, 1) == 1u);
    CHECK("get_field width 32", get_field(0xA5A5A5A5u, 0, 32) == 0xA5A5A5A5u);
    CHECK("get_field value wider than field", get_field(0x12345678u, 4, 4) == 0x7u);
    CHECK("get_field invalid range", get_field(0xFFFFFFFFu, 31, 2) == 0u);
}

static void test_set_field(void)
{
    CHECK("set_field width 1", set_field(0x0u, 0, 1, 1u) == 1u);
    CHECK("set_field pos 31 width 1", set_field(0x0u, 31, 1, 1u) == 0x80000000u);
    CHECK("set_field width 32", set_field(0x0u, 0, 32, 0xA5A5A5A5u) == 0xA5A5A5A5u);
    CHECK("set_field value wider than field", set_field(0x0u, 4, 4, 0xF0u) == 0u);
    CHECK("set_field invalid range", set_field(0x12345678u, 31, 2, 3u) == 0x12345678u);
}

static void test_sign_extend(void)
{
    CHECK("sign_extend width 1 negative", sign_extend(1u, 1) == -1);
    CHECK("sign_extend width 8 negative", sign_extend(0x80u, 8) == -128);
    CHECK("sign_extend width 32 minimum", sign_extend(0x80000000u, 32) == (int32_t)0x80000000u);
    CHECK("sign_extend width 32 max positive", sign_extend(0x7FFFFFFFu, 32) == 0x7FFFFFFF);
    CHECK("sign_extend invalid width", sign_extend(0xFFu, 0) == 0);
}

static void test_status_unpack(void)
{
    status_t example = status_unpack(0x1631u);
    CHECK("status_unpack example", example.heat == 1u && example.cool == 0u && example.fan == 0u &&
                                   example.fault == 0u && example.mode == 3u && example.setpoint == 22);

    status_t zero = status_unpack(0x0u);
    CHECK("status_unpack zero word", zero.heat == 0u && zero.cool == 0u && zero.fan == 0u &&
                                    zero.fault == 0u && zero.mode == 0u && zero.setpoint == 0);

    status_t invalid_mode = status_unpack(0x0050u);
    CHECK("status_unpack invalid mode", invalid_mode.mode == 0u && invalid_mode.setpoint == 0);
}

int main(void)
{
    test_print_binary();
    test_get_field();
    test_set_field();
    test_sign_extend();
    test_status_unpack();

    printf("SUMMARY: %d failed, %d passed\n", failures, total - failures);

    return failures == 0 ? 0 : 1;
}
