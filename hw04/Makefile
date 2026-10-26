CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

ifeq ($(OS),Windows_NT)
EXE = .exe
RM_FILES = powershell -NoProfile -Command "Remove-Item -Force -ErrorAction SilentlyContinue tally.o,events.o,tests/test_tally.o,events.exe,tests/test_tally.exe; exit 0"
else
EXE =
RM_FILES = rm -f tally.o events.o tests/test_tally.o events tests/test_tally
endif

TEST_PROGRAM = tests/test_tally$(EXE)

.PHONY: all test clean

all: events$(EXE)

events$(EXE): events.o tally.o
	$(CC) $(CFLAGS) -o $@ $^

events.o: events.c tally.h
	$(CC) $(CFLAGS) -c -o $@ $<

tally.o: tally.c tally.h
	$(CC) $(CFLAGS) -c -o $@ $<

tests/test_tally.o: tests/test_tally.c tally.h
	$(CC) $(CFLAGS) -I. -c -o $@ $<

$(TEST_PROGRAM): tests/test_tally.o tally.o
	$(CC) $(CFLAGS) -o $@ $^

test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

clean:
	$(RM_FILES)
