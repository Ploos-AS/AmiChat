#ifndef AMICHAT_MESSAGE_H
#define AMICHAT_MESSAGE_H

#include "amichat.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AmiChatMessage AmiChatMessage;

AmiChatMessage *AmiChat_MessageCreate(AmiChatRole role, const char *content);
void AmiChat_MessageFree(AmiChatMessage *message);
AmiChatRole AmiChat_MessageRole(const AmiChatMessage *message);
const char *AmiChat_MessageContent(const AmiChatMessage *message);

AmiChatResult AmiChat_ConversationAppend(
    AmiChatConversation *conversation,
    AmiChatMessage *message);

#ifdef __cplusplus
}
#endif

#endif
