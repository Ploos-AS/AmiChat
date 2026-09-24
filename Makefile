CC ?= cc
CFLAGS ?= -std=c89 -Wall -Wextra -pedantic -Iinclude

CORE = src/amichat.c
MESSAGE = src/amichat_message.c
JSON = src/amichat_json.c
TRANSPORT = src/amichat_transport.c
PROVIDER = src/amichat_openai_compat.c

.PHONY: all test clean

all: libamichat.a

libamichat.a: amichat.o amichat_message.o amichat_json.o amichat_transport.o amichat_openai_compat.o
	ar rcs $@ $^

amichat.o: $(CORE) include/amichat.h
	$(CC) $(CFLAGS) -c $(CORE) -o $@

amichat_message.o: $(MESSAGE) include/amichat_message.h
	$(CC) $(CFLAGS) -c $(MESSAGE) -o $@

amichat_json.o: $(JSON) include/amichat_json.h
	$(CC) $(CFLAGS) -c $(JSON) -o $@

amichat_transport.o: $(TRANSPORT) include/amichat_transport.h
	$(CC) $(CFLAGS) -c $(TRANSPORT) -o $@

amichat_openai_compat.o: $(PROVIDER) include/amichat_openai_compat.h include/amichat_provider.h include/amichat_transport.h
	$(CC) $(CFLAGS) -c $(PROVIDER) -o $@

test: test_core test_transport test_json
	./test_core
	./test_transport
	./test_json

test_core: $(CORE) test/test_core.c include/amichat.h
	$(CC) $(CFLAGS) $(CORE) test/test_core.c -o $@

test_transport: $(TRANSPORT) test/test_transport.c include/amichat.h include/amichat_transport.h
	$(CC) $(CFLAGS) $(TRANSPORT) test/test_transport.c -o $@

test_json: $(JSON) test/test_json.c include/amichat.h include/amichat_json.h
	$(CC) $(CFLAGS) $(JSON) test/test_json.c -o $@

clean:
	rm -f amichat.o amichat_message.o amichat_json.o amichat_transport.o amichat_openai_compat.o libamichat.a test_core test_transport test_json
