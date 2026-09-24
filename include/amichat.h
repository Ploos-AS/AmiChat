#ifndef AMICHAT_H
#define AMICHAT_H
#ifdef __cplusplus
extern "C" {
#endif
#define AMICHAT_API_VERSION 1
typedef struct AmiChatContext AmiChatContext;
typedef struct AmiChatConversation AmiChatConversation;
typedef struct AmiChatProvider AmiChatProvider;
typedef enum AmiChatRole { AMICHAT_ROLE_SYSTEM=0, AMICHAT_ROLE_USER, AMICHAT_ROLE_ASSISTANT, AMICHAT_ROLE_TOOL } AmiChatRole;
typedef enum AmiChatResult { AMICHAT_OK=0, AMICHAT_ERR_INVALID_ARGUMENT, AMICHAT_ERR_NOMEM, AMICHAT_ERR_NETWORK, AMICHAT_ERR_AUTH, AMICHAT_ERR_PROVIDER, AMICHAT_ERR_CANCELLED, AMICHAT_ERR_UNSUPPORTED } AmiChatResult;
AmiChatContext *AmiChat_Create(void);
void AmiChat_Destroy(AmiChatContext *ctx);
AmiChatConversation *AmiChat_NewConversation(AmiChatContext *ctx);
void AmiChat_FreeConversation(AmiChatConversation *conversation);
AmiChatResult AmiChat_SelectProvider(AmiChatContext *ctx, const char *provider_id);
AmiChatResult AmiChat_SelectModel(AmiChatContext *ctx, const char *model_id);
AmiChatResult AmiChat_Send(AmiChatContext *ctx, AmiChatConversation *conversation, const char *prompt);
const char *AmiChat_LastError(const AmiChatContext *ctx);
#ifdef __cplusplus
}
#endif
#endif
