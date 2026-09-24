#include "amichat_registry.h"
#include "amichat_provider.h"
#include <assert.h>
#include <string.h>
int main(void){const AmiChatProviderDefinition*p;assert(AmiChat_ProviderDefinitionCount()>=10);p=AmiChat_ProviderDefinitionFind("openrouter");assert(p);assert(p->protocol==AMICHAT_PROTOCOL_OPENAI_COMPAT);assert(strstr(p->default_url,"openrouter.ai")!=0);assert(p->capabilities&AMICHAT_CAP_STREAMING);assert(AmiChat_ProviderDefinitionFind("ollama")!=0);assert(AmiChat_ProviderDefinitionFind("missing")==0);return 0;}
