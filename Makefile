CC ?= cc
CFLAGS ?= -std=c89 -Wall -Wextra -pedantic -Iinclude

CORE = src/amichat.c
TRANSPORT = src/amichat_transport.c
PROVIDER = src/amichat_openai_compat.c

.PHONY: all test clean

all: libamichat.a

libamichat.a: amichat.o amichat_transport.o amichat_openai_compat.o
	ar rcs $@ $^

amichat.o: $(CORE) include/amichat.h
	$(CC) $(CFLAGS) -c $(CORE) -o $@

amichat_transport.o: $(TRANSPORT) include/amichat_transport.h
	$(CC) $(CFLAGS) -c $(TRANSPORT) -o $@

amichat_openai_compat.o: $(PROVIDER) include/amichat_openai_compat.h include/amichat_provider.h
	$(CC) $(CFLAGS) -c $(PROVIDER) -o $@

test: test_core test_transport
	./test_core
	./test_transport

test_core: $(CORE) test/test_core.c include/amichat.h
	$(CC) $(CFLAGS) $(CORE) test/test_core.c -o $@

test_transport: $(TRANSPORT) test/test_transport.c include/amichat.h include/amichat_transport.h
	$(CC) $(CFLAGS) $(TRANSPORT) test/test_transport.c -o $@

clean:
	rm -f amichat.o amichat_transport.o amichat_openai_compat.o libamichat.a test_core test_transport
