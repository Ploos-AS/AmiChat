#include "amichat_session.h"
#include "amichat_provider_factory.h"
#include "amichat_openai_compat.h"
#include "amichat_message.h"
#include <stdlib.h>
struct AmiChatSession { AmiChatTransport *transport; AmiChatConfig *config; AmiChatProvider provider; int provider_ready; AmiChatContext *context; AmiChatConversation *conversation; };
AmiChatSession *AmiChat_SessionCreate(AmiChatTransport*t){AmiChatSession*s;if(!t)return 0;s=(AmiChatSession*)calloc(1,sizeof(*s));if(!s)return 0;s->transport=t;s->config=AmiChat_ConfigCreate();s->context=AmiChat_Create();if(!s->config||!s->context){AmiChat_SessionDestroy(s);return 0;}s->conversation=AmiChat_NewConversation(s->context);if(!s->conversation){AmiChat_SessionDestroy(s);return 0;}return s;}
void AmiChat_SessionDestroy(AmiChatSession*s){if(!s)return;if(s->provider_ready)AmiChat_ProviderDestroy(&s->provider);AmiChat_FreeConversation(s->conversation);AmiChat_Destroy(s->context);AmiChat_ConfigDestroy(s->config);free(s);}
AmiChatConfig *AmiChat_SessionConfig(AmiChatSession*s){return s?s->config:0;}
AmiChatConversation *AmiChat_SessionConversation(AmiChatSession*s){return s?s->conversation:0;}
AmiChatResult AmiChat_SessionApplyConfig(AmiChatSession*s){AmiChatProviderConfig c;AmiChatResult r;if(!s)return AMICHAT_ERR_INVALID_ARGUMENT;if(s->provider_ready){AmiChat_ProviderDestroy(&s->provider);s->provider_ready=0;}c.provider_id=AmiChat_ConfigProvider(s->config);c.api_key=AmiChat_ConfigAPIKey(s->config);c.endpoint=AmiChat_ConfigEndpoint(s->config);c.organization=0;r=AmiChat_ProviderCreate(&s->provider,s->transport,&c);if(r==AMICHAT_OK)s->provider_ready=1;return r;}
AmiChatResult AmiChat_SessionNewConversation(AmiChatSession*s){AmiChatConversation*c;if(!s)return AMICHAT_ERR_INVALID_ARGUMENT;c=AmiChat_NewConversation(s->context);if(!c)return AMICHAT_ERR_NOMEM;AmiChat_FreeConversation(s->conversation);s->conversation=c;return AMICHAT_OK;}
AmiChatResult AmiChat_SessionSend(AmiChatSession*s,const char*prompt,AmiChatStream*stream){AmiChatMessage*m;AmiChatResult r;const char*model;if(!s||!prompt||!*prompt)return AMICHAT_ERR_INVALID_ARGUMENT;if(!s->provider_ready)return AMICHAT_ERR_PROVIDER;model=AmiChat_ConfigModel(s->config);if(!model||!*model)return AMICHAT_ERR_INVALID_ARGUMENT;m=AmiChat_MessageCreate(AMICHAT_ROLE_USER,prompt);if(!m)return AMICHAT_ERR_NOMEM;r=AmiChat_ConversationAppend(s->conversation,m);if(r!=AMICHAT_OK){AmiChat_MessageFree(m);return r;}return AmiChat_OpenAICompat_Conversation(&s->provider,model,s->conversation,stream);}
