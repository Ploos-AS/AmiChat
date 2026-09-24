#ifndef AMICHAT_PROVIDER_FACTORY_H
#define AMICHAT_PROVIDER_FACTORY_H
#include "amichat_provider.h"
#include "amichat_transport.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatProviderConfig { const char *provider_id; const char *api_key; const char *endpoint; const char *organization; } AmiChatProviderConfig;
AmiChatResult AmiChat_ProviderCreate(AmiChatProvider *provider,AmiChatTransport *transport,const AmiChatProviderConfig *config);
void AmiChat_ProviderDestroy(AmiChatProvider *provider);
#ifdef __cplusplus
}
#endif
#endif
