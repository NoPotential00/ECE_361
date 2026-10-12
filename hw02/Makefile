CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
LDLIBS ?= -lm

ifeq ($(OS),Windows_NT)
EXE = .exe
TEST_REGRESSION = powershell -NoProfile -ExecutionPolicy Bypass -File regress.ps1
FILES_TO_REMOVE = readings readings.exe main.o reading.o stats.o histogram.o test/stats_test test/stats_test.exe test/depth-O0 test/depth-O0.exe test/depth-O2 test/depth-O2.exe
WIN_FILES_TO_REMOVE = readings,readings.exe,main.o,reading.o,stats.o,histogram.o,test/stats_test,test/stats_test.exe,test/depth-O0,test/depth-O0.exe,test/depth-O2,test/depth-O2.exe
RM_FILES = powershell -NoProfile -Command "Remove-Item -Force -ErrorAction SilentlyContinue $(WIN_FILES_TO_REMOVE); exit 0"
else
EXE =
TEST_REGRESSION = sh regress.sh
FILES_TO_REMOVE = readings main.o reading.o stats.o histogram.o test/stats_test test/depth-O0 test/depth-O2
RM_FILES = rm -f $(FILES_TO_REMOVE)
endif

PROGRAM = readings$(EXE)
SOURCES = main.c reading.c stats.c histogram.c
OBJECTS = $(SOURCES:.c=.o)
TEST_PROGRAM = test/stats_test$(EXE)
DEPTH_O0 = test/depth-O0$(EXE)
DEPTH_O2 = test/depth-O2$(EXE)

.PHONY: all test bonus clean

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_PROGRAM): test/stats_test.c stats.c stats.h
	$(CC) $(CFLAGS) -I. -o $@ test/stats_test.c stats.c $(LDLIBS)

test: $(PROGRAM) $(TEST_PROGRAM)
	./$(TEST_PROGRAM)
	$(TEST_REGRESSION)

bonus: $(DEPTH_O0) $(DEPTH_O2)

$(DEPTH_O0): test/depth.c stats.c stats.h
	$(CC) -std=c11 -Wall -Wextra -Wpedantic -O0 -I. -o $@ test/depth.c stats.c

$(DEPTH_O2): test/depth.c stats.c stats.h
	$(CC) -std=c11 -Wall -Wextra -Wpedantic -O2 -I. -o $@ test/depth.c stats.c

clean:
	$(RM_FILES)
