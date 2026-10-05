CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c11 -g
CPPFLAGS ?= -I.

SRC = bits.c status.c
OBJS = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
    RM = del /Q
    TEST_SRC = tests\test_bits.c
    TEST_OBJ = tests\test_bits.o
    TEST_BIN = tests\test_bits.exe
else
    RM = rm -f
    TEST_SRC = tests/test_bits.c
    TEST_OBJ = tests/test_bits.o
    TEST_BIN = tests/test_bits
endif

.PHONY: all tests clean

all: $(OBJS)

tests: $(TEST_BIN)
ifeq ($(OS),Windows_NT)
	$(TEST_BIN)
else
	./$(TEST_BIN)
endif

bits.o: bits.c bits.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c bits.c -o bits.o

status.o: status.c status.h bits.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c status.c -o status.o

$(TEST_OBJ): $(TEST_SRC) bits.h status.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)

$(TEST_BIN): $(OBJS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(TEST_OBJ) -o $(TEST_BIN)

clean:
	$(RM) $(OBJS) $(TEST_OBJ) $(TEST_BIN)
