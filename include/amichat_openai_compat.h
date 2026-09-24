#ifndef AMICHAT_OPENAI_COMPAT_H
#define AMICHAT_OPENAI_COMPAT_H
#include "amichat.h"
#include "amichat_provider.h"
#include "amichat_transport.h"
#include "amichat_request.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatOpenAICompatConfig { const char *base_url; const char *api_key; const char *organization; } AmiChatOpenAICompatConfig;
AmiChatResult AmiChat_OpenAICompat_Init(AmiChatProvider *,AmiChatTransport *,const AmiChatOpenAICompatConfig *);
AmiChatResult AmiChat_OpenAICompat_Chat(AmiChatProvider *,const AmiChatRequest *,AmiChatStream *);
AmiChatResult AmiChat_OpenAICompat_Conversation(AmiChatProvider *,const char *,const AmiChatConversation *,AmiChatStream *);
#ifdef __cplusplus
}
#endif
#endif
