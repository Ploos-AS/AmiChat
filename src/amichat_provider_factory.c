#include "amichat_provider_factory.h"
#include "amichat_registry.h"
#include "amichat_openai_compat.h"
#include <string.h>
AmiChatResult AmiChat_ProviderCreate(AmiChatProvider*p,AmiChatTransport*t,const AmiChatProviderConfig*c){const AmiChatProviderDefinition*d;AmiChatOpenAICompatConfig oc;const char*url;if(!p||!t||!c||!c->provider_id)return AMICHAT_ERR_INVALID_ARGUMENT;memset(p,0,sizeof(*p));d=AmiChat_ProviderDefinitionFind(c->provider_id);if(!d)return AMICHAT_ERR_INVALID_ARGUMENT;url=c->endpoint?c->endpoint:d->default_url;if(!url||!*url)return AMICHAT_ERR_INVALID_ARGUMENT;switch(d->protocol){case AMICHAT_PROTOCOL_OPENAI_COMPAT:oc.base_url=url;oc.api_key=c->api_key;oc.organization=c->organization;return AmiChat_OpenAICompat_Init(p,t,&oc);case AMICHAT_PROTOCOL_ANTHROPIC:case AMICHAT_PROTOCOL_GEMINI:default:return AMICHAT_ERR_UNSUPPORTED;}}
void AmiChat_ProviderDestroy(AmiChatProvider*p){if(!p)return;if(p->ops&&p->ops->destroy)p->ops->destroy(p);p->ops=0;p->userdata=0;}
