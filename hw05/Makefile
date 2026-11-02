CC      ?= gcc
CFLAGS  ?= -std=c11 -Wall -Wextra -pedantic

ifeq ($(OS),Windows_NT)
    EXEEXT := .exe
    RM     := del /Q
    RUN    :=
else
    EXEEXT :=
    RM     := rm -f
    RUN    := ./
endif

PROGRAM := lock$(EXEEXT)
TEST    := test_lock$(EXEEXT)
BONUS_TEST := test_check$(EXEEXT)

ifeq ($(OS),Windows_NT)
    CLEAN_FILES := $(PROGRAM) $(TEST) $(BONUS_TEST) main.o lock.o check.o tests\\test_lock.o tests\\test_check.o
else
    CLEAN_FILES := $(PROGRAM) $(TEST) $(BONUS_TEST) main.o lock.o check.o tests/test_lock.o tests/test_check.o
endif

.PHONY: all test bonus run clean

all: $(PROGRAM) $(TEST) $(BONUS_TEST)

$(PROGRAM): main.o lock.o
	$(CC) $(CFLAGS) $^ -o $@

$(TEST): tests/test_lock.o lock.o
	$(CC) $(CFLAGS) $^ -o $@

$(BONUS_TEST): tests/test_check.o check.o lock.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c lock.h
	$(CC) $(CFLAGS) -c $< -o $@

lock.o: lock.c lock.h
	$(CC) $(CFLAGS) -c $< -o $@

check.o: check.c check.h lock.h
	$(CC) $(CFLAGS) -c $< -o $@

tests/test_lock.o: tests/test_lock.c lock.h
	$(CC) $(CFLAGS) -c $< -o $@

tests/test_check.o: tests/test_check.c check.h lock.h
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST)
	$(RUN)$(TEST)

bonus: $(BONUS_TEST)
	$(RUN)$(BONUS_TEST)

run: $(PROGRAM)
	$(RUN)$(PROGRAM) < data/codes.txt

clean:
	$(RM) $(CLEAN_FILES)
