#include "amichat.h"
#include <stdlib.h>
#include <string.h>

struct AmiChatConversation {
    char *title;
};

struct AmiChatContext {
    char *provider_id;
    char *model_id;
    char *last_error;
};

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

static void set_string(char **dst, const char *src)
{
    char *p = dup_string(src);
    free(*dst);
    *dst = p;
}

AmiChatContext *AmiChat_Create(void)
{
    return (AmiChatContext *)calloc(1, sizeof(AmiChatContext));
}

void AmiChat_Destroy(AmiChatContext *ctx)
{
    if (!ctx) return;
    free(ctx->provider_id);
    free(ctx->model_id);
    free(ctx->last_error);
    free(ctx);
}

AmiChatConversation *AmiChat_NewConversation(AmiChatContext *ctx)
{
    AmiChatConversation *conversation;
    (void)ctx;
    conversation = (AmiChatConversation *)calloc(1, sizeof(*conversation));
    if (conversation) conversation->title = dup_string("New conversation");
    return conversation;
}

void AmiChat_FreeConversation(AmiChatConversation *conversation)
{
    if (!conversation) return;
    free(conversation->title);
    free(conversation);
}

AmiChatResult AmiChat_SelectProvider(AmiChatContext *ctx, const char *provider_id)
{
    if (!ctx || !provider_id || !*provider_id) return AMICHAT_ERR_INVALID_ARGUMENT;
    set_string(&ctx->provider_id, provider_id);
    return ctx->provider_id ? AMICHAT_OK : AMICHAT_ERR_NOMEM;
}

AmiChatResult AmiChat_SelectModel(AmiChatContext *ctx, const char *model_id)
{
    if (!ctx || !model_id || !*model_id) return AMICHAT_ERR_INVALID_ARGUMENT;
    set_string(&ctx->model_id, model_id);
    return ctx->model_id ? AMICHAT_OK : AMICHAT_ERR_NOMEM;
}

AmiChatResult AmiChat_Send(AmiChatContext *ctx,
                           AmiChatConversation *conversation,
                           const char *prompt)
{
    (void)conversation;
    if (!ctx || !prompt || !*prompt) return AMICHAT_ERR_INVALID_ARGUMENT;
    set_string(&ctx->last_error, "Provider transport not implemented yet");
    return AMICHAT_ERR_UNSUPPORTED;
}

const char *AmiChat_LastError(const AmiChatContext *ctx)
{
    return ctx && ctx->last_error ? ctx->last_error : "";
}
