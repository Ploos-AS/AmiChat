#ifndef AMICHAT_JSON_H
#define AMICHAT_JSON_H

#include "amichat.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Small JSON string encoder used by provider adapters. */
AmiChatResult AmiChat_JSONAppendString(
    char *buffer,
    size_t capacity,
    size_t *length,
    const char *value);

#ifdef __cplusplus
}
#endif

#endif
