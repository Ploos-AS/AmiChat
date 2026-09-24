#ifndef AMICHAT_REQUEST_H
#define AMICHAT_REQUEST_H
#include "amichat.h"
#include "amichat_stream.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatRequest { const char *model; const char *system_prompt; const char *user_prompt; AmiChatStream *stream; } AmiChatRequest;
AmiChatResult AmiChat_RequestValidate(const AmiChatRequest *request);
#ifdef __cplusplus
}
#endif
#endif
