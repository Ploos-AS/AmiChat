#include "amichat_message.h"
#include <stdlib.h>
#include <string.h>

struct AmiChatMessage {
    AmiChatRole role;
    char *content;
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

AmiChatMessage *AmiChat_MessageCreate(AmiChatRole role, const char *content)
{
    AmiChatMessage *message;
    if (!content) return NULL;
    message = (AmiChatMessage *)calloc(1, sizeof(*message));
    if (!message) return NULL;
    message->role = role;
    message->content = dup_string(content);
    if (!message->content) {
        free(message);
        return NULL;
    }
    return message;
}

void AmiChat_MessageFree(AmiChatMessage *message)
{
    if (!message) return;
    free(message->content);
    free(message);
}

AmiChatRole AmiChat_MessageRole(const AmiChatMessage *message)
{
    return message ? message->role : AMICHAT_ROLE_SYSTEM;
}

const char *AmiChat_MessageContent(const AmiChatMessage *message)
{
    return message ? message->content : NULL;
}

AmiChatResult AmiChat_ConversationAppend(
    AmiChatConversation *conversation,
    AmiChatMessage *message)
{
    (void)conversation;
    (void)message;
    /* Conversation storage is implemented in the next core increment. */
    return (conversation && message) ? AMICHAT_ERR_UNSUPPORTED
                                     : AMICHAT_ERR_INVALID_ARGUMENT;
}
