CC ?= cc
CFLAGS ?= -std=c89 -Wall -Wextra -pedantic -Iinclude

CORE = src/amichat.c
MESSAGE = src/amichat_message.c
JSON = src/amichat_json.c
STREAM = src/amichat_stream.c
REQUEST = src/amichat_request.c
SSE = src/amichat_sse.c
TRANSPORT = src/amichat_transport.c
PROVIDER = src/amichat_openai_compat.c

.PHONY: all test clean

all: libamichat.a

libamichat.a: amichat.o amichat_message.o amichat_json.o amichat_stream.o amichat_request.o amichat_sse.o amichat_transport.o amichat_openai_compat.o
	ar rcs $@ $^

amichat.o: $(CORE) include/amichat.h
	$(CC) $(CFLAGS) -c $(CORE) -o $@

amichat_message.o: $(MESSAGE) include/amichat_message.h
	$(CC) $(CFLAGS) -c $(MESSAGE) -o $@

amichat_json.o: $(JSON) include/amichat_json.h
	$(CC) $(CFLAGS) -c $(JSON) -o $@

amichat_stream.o: $(STREAM) include/amichat_stream.h
	$(CC) $(CFLAGS) -c $(STREAM) -o $@

amichat_request.o: $(REQUEST) include/amichat_request.h
	$(CC) $(CFLAGS) -c $(REQUEST) -o $@

amichat_sse.o: $(SSE) include/amichat_sse.h include/amichat_stream.h include/amichat_json.h
	$(CC) $(CFLAGS) -c $(SSE) -o $@

amichat_transport.o: $(TRANSPORT) include/amichat_transport.h
	$(CC) $(CFLAGS) -c $(TRANSPORT) -o $@

amichat_openai_compat.o: $(PROVIDER) include/amichat_openai_compat.h include/amichat_provider.h include/amichat_transport.h
	$(CC) $(CFLAGS) -c $(PROVIDER) -o $@

test: test_core test_transport test_json test_stream test_request test_sse test_openai_stream test_stream test_request test_sse test_openai_stream
	./test_core
	./test_transport
	./test_json
	./test_stream
	./test_request
	./test_sse
	./test_openai_stream

test_core: $(CORE) test/test_core.c include/amichat.h
	$(CC) $(CFLAGS) $(CORE) test/test_core.c -o $@

test_transport: $(TRANSPORT) test/test_transport.c include/amichat.h include/amichat_transport.h
	$(CC) $(CFLAGS) $(TRANSPORT) test/test_transport.c -o $@

test_json: $(JSON) test/test_json.c include/amichat.h include/amichat_json.h
	$(CC) $(CFLAGS) $(JSON) test/test_json.c -o $@

test_stream: $(STREAM) test/test_stream.c include/amichat.h include/amichat_stream.h
	$(CC) $(CFLAGS) $(STREAM) test/test_stream.c -o $@

test_request: $(REQUEST) test/test_request.c include/amichat.h include/amichat_request.h
	$(CC) $(CFLAGS) $(REQUEST) test/test_request.c -o $@

test_sse: $(SSE) $(STREAM) $(JSON) test/test_sse.c include/amichat_sse.h
	$(CC) $(CFLAGS) $(SSE) $(STREAM) $(JSON) test/test_sse.c -o $@

test_openai_stream: $(PROVIDER) $(TRANSPORT) $(REQUEST) $(SSE) $(STREAM) $(JSON) test/test_openai_stream.c
	$(CC) $(CFLAGS) $(PROVIDER) $(TRANSPORT) $(REQUEST) $(SSE) $(STREAM) $(JSON) test/test_openai_stream.c -o $@

clean:
	rm -f amichat.o amichat_message.o amichat_json.o amichat_stream.o amichat_request.o amichat_sse.o amichat_transport.o amichat_openai_compat.o libamichat.a test_core test_transport test_json
