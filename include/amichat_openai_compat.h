#ifndef AMICHAT_OPENAI_COMPAT_H
#define AMICHAT_OPENAI_COMPAT_H

#include "amichat.h"
#include "amichat_transport.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AmiChatOpenAICompatConfig {
    const char *base_url;
    const char *api_key;
    const char *organization;
} AmiChatOpenAICompatConfig;

AmiChatResult AmiChat_OpenAICompat_Init(
    AmiChatProvider *provider,
    AmiChatTransport *transport,
    const AmiChatOpenAICompatConfig *config);

#ifdef __cplusplus
}
#endif

#endif
