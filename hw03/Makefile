CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

ifeq ($(OS),Windows_NT)
EXE = .exe
RM_FILES = powershell -NoProfile -Command "Remove-Item -Force -ErrorAction SilentlyContinue ptr.o,tests/test_ptr.o,tests/test_ptr,tests/test_ptr.exe; exit 0"
else
EXE =
RM_FILES = rm -f ptr.o tests/test_ptr.o tests/test_ptr tests/test_ptr.exe
endif

TEST_PROGRAM = tests/test_ptr$(EXE)

.PHONY: all test clean

all: $(TEST_PROGRAM)

ptr.o: ptr.c ptr.h
	$(CC) $(CFLAGS) -c -o $@ $<

tests/test_ptr.o: tests/test_ptr.c ptr.h
	$(CC) $(CFLAGS) -I. -c -o $@ $<

$(TEST_PROGRAM): tests/test_ptr.o ptr.o
	$(CC) $(CFLAGS) -o $@ $^

test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

clean:
	$(RM_FILES)
