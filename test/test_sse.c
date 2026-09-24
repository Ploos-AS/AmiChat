#include "amichat_sse.h"
#include <assert.h>
#include <string.h>

typedef struct State { char text[64]; size_t length; int final; } State;

static int cb(const char *d, size_t n, int final, void *userdata)
{
    State *s = (State *)userdata;
    if (n) {
        memcpy(s->text + s->length, d, n);
        s->length += n;
        s->text[s->length] = '\0';
    }
    if (final)
        s->final = 1;
    return 1;
}

int main(void)
{
    static const char first[] = "data: {\"delta\":{\"content\":\"Hel";
    static const char second[] =
        "lo\"}}\n\n"
        "data: {\"delta\":{\"content\":\" Amiga\"}}\n\n"
        "data: [DONE]\n\n";
    AmiChatSSEParser parser;
    AmiChatStream stream;
    State state;

    state.text[0] = '\0';
    state.length = 0;
    state.final = 0;
    AmiChat_StreamInit(&stream, cb, &state);
    AmiChat_SSEInit(&parser, &stream);
    assert(AmiChat_SSEFeed(&parser, first, strlen(first)) == AMICHAT_OK);
    assert(AmiChat_SSEFeed(&parser, second, strlen(second)) == AMICHAT_OK);
    assert(strcmp(state.text, "Hello Amiga") == 0);
    assert(state.final == 1);
    return 0;
}
