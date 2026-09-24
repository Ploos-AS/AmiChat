CC ?= cc
AR ?= ar
CFLAGS ?= -std=c89 -Wall -Wextra -pedantic -Iinclude

CORE_SRCS = src/amichat.c src/amichat_message.c src/amichat_json.c src/amichat_stream.c \
	src/amichat_request.c src/amichat_sse.c src/amichat_transport.c \
	src/amichat_openai_compat.c src/amichat_registry.c src/amichat_provider_factory.c \
	src/amichat_config.c src/amichat_session.c src/amichat_arexx.c \
	src/amichat_worker.c src/amichat_transcript.c
CORE_OBJS = $(CORE_SRCS:src/%.c=%.o)

TESTS = test_core test_transport test_json test_stream test_request test_sse \
	test_openai_stream test_conversation test_openai_history test_reply_capture \
	test_registry test_provider_factory test_config test_session test_arexx \
	test_worker test_transcript

.PHONY: all test clean

all: libamichat.a

libamichat.a: $(CORE_OBJS)
	$(AR) rcs $@ $^

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TESTS)
	@set -e; for t in $(TESTS); do echo "==> $$t"; ./$$t; done

test_core: src/amichat.c src/amichat_message.c test/test_core.c
	$(CC) $(CFLAGS) $^ -o $@
test_transport: src/amichat_transport.c test/test_transport.c
	$(CC) $(CFLAGS) $^ -o $@
test_json: src/amichat_json.c test/test_json.c
	$(CC) $(CFLAGS) $^ -o $@
test_stream: src/amichat_stream.c test/test_stream.c
	$(CC) $(CFLAGS) $^ -o $@
test_request: src/amichat_request.c test/test_request.c
	$(CC) $(CFLAGS) $^ -o $@
test_sse: src/amichat_sse.c src/amichat_stream.c src/amichat_json.c test/test_sse.c
	$(CC) $(CFLAGS) $^ -o $@
test_openai_stream: src/amichat_openai_compat.c src/amichat_transport.c src/amichat_request.c src/amichat_sse.c src/amichat_stream.c src/amichat_json.c src/amichat_message.c src/amichat.c test/test_openai_stream.c
	$(CC) $(CFLAGS) $^ -o $@
test_conversation: src/amichat.c src/amichat_message.c test/test_conversation.c
	$(CC) $(CFLAGS) $^ -o $@
test_openai_history: src/amichat_openai_compat.c src/amichat.c src/amichat_message.c src/amichat_transport.c src/amichat_request.c src/amichat_sse.c src/amichat_stream.c src/amichat_json.c test/test_openai_history.c
	$(CC) $(CFLAGS) $^ -o $@
test_reply_capture: src/amichat_openai_compat.c src/amichat.c src/amichat_message.c src/amichat_transport.c src/amichat_request.c src/amichat_sse.c src/amichat_stream.c src/amichat_json.c test/test_reply_capture.c
	$(CC) $(CFLAGS) $^ -o $@
test_registry: src/amichat_registry.c test/test_registry.c
	$(CC) $(CFLAGS) $^ -o $@
test_provider_factory: src/amichat_provider_factory.c src/amichat_registry.c src/amichat_openai_compat.c src/amichat_transport.c src/amichat_request.c src/amichat_sse.c src/amichat_stream.c src/amichat_json.c src/amichat_message.c src/amichat.c test/test_provider_factory.c
	$(CC) $(CFLAGS) $^ -o $@
test_config: src/amichat_config.c test/test_config.c
	$(CC) $(CFLAGS) $^ -o $@
test_session: src/amichat_session.c src/amichat_provider_factory.c src/amichat_registry.c src/amichat_openai_compat.c src/amichat_config.c src/amichat.c src/amichat_message.c src/amichat_transport.c src/amichat_request.c src/amichat_sse.c src/amichat_stream.c src/amichat_json.c test/test_session.c
	$(CC) $(CFLAGS) $^ -o $@
test_arexx: src/amichat_arexx.c src/amichat_session.c src/amichat_provider_factory.c src/amichat_registry.c src/amichat_openai_compat.c src/amichat_config.c src/amichat.c src/amichat_message.c src/amichat_transport.c src/amichat_request.c src/amichat_sse.c src/amichat_stream.c src/amichat_json.c test/test_arexx.c
	$(CC) $(CFLAGS) $^ -o $@
test_worker: src/amichat_worker.c src/amichat_session.c src/amichat_provider_factory.c src/amichat_registry.c src/amichat_openai_compat.c src/amichat_config.c src/amichat.c src/amichat_message.c src/amichat_transport.c src/amichat_request.c src/amichat_sse.c src/amichat_stream.c src/amichat_json.c test/test_worker.c
	$(CC) $(CFLAGS) $^ -o $@
test_transcript: src/amichat_transcript.c src/amichat.c src/amichat_message.c test/test_transcript.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(CORE_OBJS) libamichat.a $(TESTS) test-config.tmp
