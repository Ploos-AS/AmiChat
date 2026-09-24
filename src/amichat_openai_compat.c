#include "amichat_openai_compat.h"
#include <stdlib.h>
#include <string.h>

typedef struct OpenAICompatState {
    AmiChatTransport *transport;
    char *base_url;
    char *api_key;
    char *organization;
} OpenAICompatState;

static char *dup_string(const char *s)
{
    size_t n;
    char *p;
    if (!s) return NULL;
    n = strlen(s) + 1;
    p = (char *)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}

static void free_state(OpenAICompatState *s)
{
    if (!s) return;
    free(s->base_url);
    free(s->api_key);
    free(s->organization);
    free(s);
}

static AmiChatResult configure(AmiChatProvider *provider, const char *config)
{
    (void)provider;
    (void)config;
    return AMICHAT_ERR_UNSUPPORTED;
}

static AmiChatResult list_models(AmiChatProvider *provider)
{
    (void)provider;
    return AMICHAT_ERR_UNSUPPORTED;
}

static AmiChatResult send_message(AmiChatProvider *provider,
                                  AmiChatConversation *conversation)
{
    (void)provider;
    (void)conversation;
    return AMICHAT_ERR_UNSUPPORTED;
}

static AmiChatResult cancel(AmiChatProvider *provider)
{
    (void)provider;
    return AMICHAT_ERR_UNSUPPORTED;
}

static void destroy(AmiChatProvider *provider)
{
    (void)provider;
}

static const AmiChatProviderOps openai_compat_ops = {
    configure,
    list_models,
    send_message,
    cancel,
    destroy
};

AmiChatResult AmiChat_OpenAICompat_Init(
    AmiChatProvider *provider,
    AmiChatTransport *transport,
    const AmiChatOpenAICompatConfig *config)
{
    OpenAICompatState *state;

    if (!provider || !transport || !config || !config->base_url)
        return AMICHAT_ERR_INVALID_ARGUMENT;

    state = (OpenAICompatState *)calloc(1, sizeof(*state));
    if (!state) return AMICHAT_ERR_NOMEM;

    state->transport = transport;
    state->base_url = dup_string(config->base_url);
    state->api_key = dup_string(config->api_key);
    state->organization = dup_string(config->organization);

    if (!state->base_url ||
        (config->api_key && !state->api_key) ||
        (config->organization && !state->organization)) {
        free_state(state);
        return AMICHAT_ERR_NOMEM;
    }

    provider->ops = &openai_compat_ops;
    provider->userdata = state;
    return AMICHAT_OK;
}
