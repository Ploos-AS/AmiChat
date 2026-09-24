#ifndef AMICHAT_CONFIG_H
#define AMICHAT_CONFIG_H
#include "amichat.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatConfig AmiChatConfig;
AmiChatConfig *AmiChat_ConfigCreate(void);
void AmiChat_ConfigDestroy(AmiChatConfig *config);
AmiChatResult AmiChat_ConfigSetProvider(AmiChatConfig *config,const char *value);
AmiChatResult AmiChat_ConfigSetModel(AmiChatConfig *config,const char *value);
AmiChatResult AmiChat_ConfigSetEndpoint(AmiChatConfig *config,const char *value);
AmiChatResult AmiChat_ConfigSetAPIKey(AmiChatConfig *config,const char *value);
const char *AmiChat_ConfigProvider(const AmiChatConfig *config);
const char *AmiChat_ConfigModel(const AmiChatConfig *config);
const char *AmiChat_ConfigEndpoint(const AmiChatConfig *config);
const char *AmiChat_ConfigAPIKey(const AmiChatConfig *config);
AmiChatResult AmiChat_ConfigSavePublic(const AmiChatConfig *config,const char *path);
#ifdef __cplusplus
}
#endif
#endif
