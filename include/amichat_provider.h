#ifndef AMICHAT_PROVIDER_H
#define AMICHAT_PROVIDER_H
#include "amichat.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatProviderInfo { const char *id; const char *name; unsigned long capabilities; } AmiChatProviderInfo;
enum { AMICHAT_CAP_STREAMING=1UL<<0, AMICHAT_CAP_VISION=1UL<<1, AMICHAT_CAP_TOOLS=1UL<<2, AMICHAT_CAP_ATTACHMENTS=1UL<<3, AMICHAT_CAP_REASONING=1UL<<4 };
typedef struct AmiChatProviderOps { AmiChatResult (*configure)(AmiChatProvider *, const char *); AmiChatResult (*list_models)(AmiChatProvider *); AmiChatResult (*send)(AmiChatProvider *, AmiChatConversation *); AmiChatResult (*cancel)(AmiChatProvider *); void (*destroy)(AmiChatProvider *); } AmiChatProviderOps;
#ifdef __cplusplus
}
#endif
#endif
