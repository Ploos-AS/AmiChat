#ifndef AMICHAT_SESSION_H
#define AMICHAT_SESSION_H
#include "amichat.h"
#include "amichat_config.h"
#include "amichat_transport.h"
#include "amichat_provider.h"
#include "amichat_stream.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatSession AmiChatSession;
AmiChatSession *AmiChat_SessionCreate(AmiChatTransport *transport);
void AmiChat_SessionDestroy(AmiChatSession *session);
AmiChatConfig *AmiChat_SessionConfig(AmiChatSession *session);
AmiChatConversation *AmiChat_SessionConversation(AmiChatSession *session);
AmiChatResult AmiChat_SessionApplyConfig(AmiChatSession *session);
AmiChatResult AmiChat_SessionNewConversation(AmiChatSession *session);
AmiChatResult AmiChat_SessionSend(AmiChatSession *session,const char *prompt,AmiChatStream *stream);
#ifdef __cplusplus
}
#endif
#endif
