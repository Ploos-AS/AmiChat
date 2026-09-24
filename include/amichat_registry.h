#ifndef AMICHAT_REGISTRY_H
#define AMICHAT_REGISTRY_H
#include <stddef.h>
#include "amichat.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef enum AmiChatProviderProtocol { AMICHAT_PROTOCOL_OPENAI_COMPAT=0, AMICHAT_PROTOCOL_ANTHROPIC, AMICHAT_PROTOCOL_GEMINI } AmiChatProviderProtocol;
typedef struct AmiChatProviderDefinition { const char *id; const char *name; AmiChatProviderProtocol protocol; const char *default_url; unsigned long capabilities; } AmiChatProviderDefinition;
size_t AmiChat_ProviderDefinitionCount(void);
const AmiChatProviderDefinition *AmiChat_ProviderDefinitionAt(size_t index);
const AmiChatProviderDefinition *AmiChat_ProviderDefinitionFind(const char *id);
#ifdef __cplusplus
}
#endif
#endif
