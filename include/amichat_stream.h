#ifndef AMICHAT_STREAM_H
#define AMICHAT_STREAM_H
#include "amichat.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef int (*AmiChatStreamCallback)(const char *, size_t, int, void *);
typedef struct AmiChatStream { AmiChatStreamCallback callback; void *userdata; int cancelled; } AmiChatStream;
void AmiChat_StreamInit(AmiChatStream *, AmiChatStreamCallback, void *);
void AmiChat_StreamCancel(AmiChatStream *);
int AmiChat_StreamCancelled(const AmiChatStream *);
AmiChatResult AmiChat_StreamEmit(AmiChatStream *, const char *, size_t, int);
#ifdef __cplusplus
}
#endif
#endif
