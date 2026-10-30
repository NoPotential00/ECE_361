CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g
LDLIBS = -lm

TARGET = kiln
SOURCES = main.c sensor.c fsm.c store.c aux.c report.c iom361_r4.c
OBJECTS = $(SOURCES:.c=.o)
DEPS = $(OBJECTS:.o=.d)
TEST_TARGET = tests/test_store
SAN = -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: all test clean
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

$(TEST_TARGET): tests/test_store.c store.c store.h sensor.h fsm.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SAN) -I. $(LDFLAGS) -o $@ tests/test_store.c store.c $(LDLIBS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	$(RM) $(TARGET) $(OBJECTS) $(DEPS) $(TEST_TARGET)
