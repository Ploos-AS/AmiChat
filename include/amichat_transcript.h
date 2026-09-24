#ifndef AMICHAT_TRANSCRIPT_H
#define AMICHAT_TRANSCRIPT_H
#include <stddef.h>
#include "amichat.h"
#include "amichat_message.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatTranscript AmiChatTranscript;
AmiChatTranscript *AmiChat_TranscriptCreate(void);
void AmiChat_TranscriptDestroy(AmiChatTranscript *transcript);
AmiChatResult AmiChat_TranscriptBegin(AmiChatTranscript *transcript,AmiChatRole role);
AmiChatResult AmiChat_TranscriptAppend(AmiChatTranscript *transcript,const char *data,size_t size);
void AmiChat_TranscriptFinish(AmiChatTranscript *transcript);
void AmiChat_TranscriptClear(AmiChatTranscript *transcript);
AmiChatResult AmiChat_TranscriptRebuild(AmiChatTranscript *transcript,const AmiChatConversation *conversation);
const char *AmiChat_TranscriptText(const AmiChatTranscript *transcript);
size_t AmiChat_TranscriptLength(const AmiChatTranscript *transcript);
int AmiChat_TranscriptActive(const AmiChatTranscript *transcript);
#ifdef __cplusplus
}
#endif
#endif
