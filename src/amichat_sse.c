#include "amichat_sse.h"
#include "amichat_json.h"
#include <string.h>

static AmiChatResult event(AmiChatSSEParser *p, const char *d, size_t n)
{
    char json[4096], content[2048];
    if (n == 6 && memcmp(d, "[DONE]", 6) == 0) {
        p->done = 1;
        return AmiChat_StreamEmit(p->stream, "", 0, 1);
    }
    if (n >= sizeof(json))
        return AMICHAT_ERR_PROVIDER;
    memcpy(json, d, n);
    json[n] = '\0';
    if (AmiChat_JSONFindString(json, "content", content, sizeof(content)))
        return AmiChat_StreamEmit(p->stream, content, strlen(content), 0);
    return AMICHAT_OK;
}

void AmiChat_SSEInit(AmiChatSSEParser *p, AmiChatStream *s)
{
    if (!p) return;
    p->length = 0;
    p->done = 0;
    p->stream = s;
    p->buffer[0] = '\0';
}

AmiChatResult AmiChat_SSEFeed(AmiChatSSEParser *p, const char *d, size_t n)
{
    size_t i, consumed = 0;
    AmiChatResult r;
    if (!p || (!d && n))
        return AMICHAT_ERR_INVALID_ARGUMENT;
    if (p->done)
        return AMICHAT_OK;
    if (p->length + n >= sizeof(p->buffer))
        return AMICHAT_ERR_PROVIDER;

    memcpy(p->buffer + p->length, d, n);
    p->length += n;
    p->buffer[p->length] = '\0';

    i = 0;
    while (i + 1 < p->length) {
        size_t end, line;
        if (p->buffer[i] != '\n' || p->buffer[i + 1] != '\n') {
            i++;
            continue;
        }
        end = i;
        line = consumed;
        while (line < end) {
            size_t e = line;
            while (e < end && p->buffer[e] != '\n')
                e++;
            if (e - line >= 5 && memcmp(p->buffer + line, "data:", 5) == 0) {
                size_t x = line + 5;
                while (x < e && (p->buffer[x] == ' ' || p->buffer[x] == '\t'))
                    x++;
                r = event(p, p->buffer + x, e - x);
                if (r != AMICHAT_OK)
                    return r;
            }
            line = e + 1;
        }
        consumed = i + 2;
        i = consumed;
        if (p->done)
            break;
    }

    if (consumed) {
        memmove(p->buffer, p->buffer + consumed, p->length - consumed);
        p->length -= consumed;
        p->buffer[p->length] = '\0';
    }
    return AMICHAT_OK;
}

AmiChatResult AmiChat_SSEFinish(AmiChatSSEParser *p)
{
    if (!p)
        return AMICHAT_ERR_INVALID_ARGUMENT;
    if (p->done)
        return AMICHAT_OK;
    if (p->length) {
        AmiChatResult r = AmiChat_SSEFeed(p, "\n\n", 2);
        if (r != AMICHAT_OK)
            return r;
    }
    if (!p->done)
        return AmiChat_StreamEmit(p->stream, "", 0, 1);
    return AMICHAT_OK;
}
