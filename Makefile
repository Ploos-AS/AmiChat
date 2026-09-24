CC ?= cc
CFLAGS ?= -std=c89 -Wall -Wextra -pedantic -Iinclude

CORE = src/amichat.c

.PHONY: all test clean

all: libamichat.a

libamichat.a: amichat.o
	ar rcs $@ $<

amichat.o: $(CORE) include/amichat.h
	$(CC) $(CFLAGS) -c $(CORE) -o $@

test: test_core
	./test_core

test_core: $(CORE) test/test_core.c include/amichat.h
	$(CC) $(CFLAGS) $(CORE) test/test_core.c -o $@

clean:
	rm -f amichat.o libamichat.a test_core
