#include "amichat_json.h"
#include <stddef.h>

static int append_char(char *buffer, size_t capacity, size_t *length, char c)
{
    if (!buffer || !length || *length + 1 >= capacity)
        return 0;
    buffer[(*length)++] = c;
    buffer[*length] = '\0';
    return 1;
}

static int append_hex(char *buffer, size_t capacity, size_t *length,
                      unsigned char value)
{
    static const char hex[] = "0123456789abcdef";
    return append_char(buffer, capacity, length, hex[(value >> 4) & 15]) &&
           append_char(buffer, capacity, length, hex[value & 15]);
}

AmiChatResult AmiChat_JSONAppendString(
    char *buffer, size_t capacity, size_t *length, const char *value)
{
    const unsigned char *p;
    if (!buffer || !length || !value || *length >= capacity)
        return AMICHAT_ERR_INVALID_ARGUMENT;

    if (!append_char(buffer, capacity, length, '"'))
        return AMICHAT_ERR_NOMEM;

    for (p = (const unsigned char *)value; *p; ++p) {
        if (*p == '"' || *p == '\') {
            if (!append_char(buffer, capacity, length, '\') ||
                !append_char(buffer, capacity, length, (char)*p))
                return AMICHAT_ERR_NOMEM;
        } else if (*p < 0x20) {
            if (!append_char(buffer, capacity, length, '\'))
                return AMICHAT_ERR_NOMEM;
            switch (*p) {
            case '\b': if (!append_char(buffer, capacity, length, 'b')) return AMICHAT_ERR_NOMEM; break;
            case '\f': if (!append_char(buffer, capacity, length, 'f')) return AMICHAT_ERR_NOMEM; break;
            case '\n': if (!append_char(buffer, capacity, length, 'n')) return AMICHAT_ERR_NOMEM; break;
            case '\r': if (!append_char(buffer, capacity, length, 'r')) return AMICHAT_ERR_NOMEM; break;
            case '\t': if (!append_char(buffer, capacity, length, 't')) return AMICHAT_ERR_NOMEM; break;
            default:
                if (!append_char(buffer, capacity, length, 'u') ||
                    !append_char(buffer, capacity, length, '0') ||
                    !append_char(buffer, capacity, length, '0') ||
                    !append_hex(buffer, capacity, length, *p))
                    return AMICHAT_ERR_NOMEM;
                break;
            }
        } else if (!append_char(buffer, capacity, length, (char)*p)) {
            return AMICHAT_ERR_NOMEM;
        }
    }

    if (!append_char(buffer, capacity, length, '"'))
        return AMICHAT_ERR_NOMEM;
    return AMICHAT_OK;
}
