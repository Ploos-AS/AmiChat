#ifndef AMICHAT_SSE_H
#define AMICHAT_SSE_H
#include <stddef.h>
#include "amichat.h"
#include "amichat_stream.h"
#ifdef __cplusplus
extern "C" {
#endif
#define AMICHAT_SSE_BUFFER_SIZE 8192
typedef struct AmiChatSSEParser { char buffer[AMICHAT_SSE_BUFFER_SIZE]; size_t length; int done; AmiChatStream *stream; } AmiChatSSEParser;
void AmiChat_SSEInit(AmiChatSSEParser *parser,AmiChatStream *stream);
AmiChatResult AmiChat_SSEFeed(AmiChatSSEParser *parser,const char *data,size_t length);
AmiChatResult AmiChat_SSEFinish(AmiChatSSEParser *parser);
#ifdef __cplusplus
}
#endif
#endif
