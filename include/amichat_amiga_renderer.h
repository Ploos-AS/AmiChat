#ifndef AMICHAT_AMIGA_RENDERER_H
#define AMICHAT_AMIGA_RENDERER_H
#include "amichat_transcript.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatAmigaRenderer AmiChatAmigaRenderer;
AmiChatAmigaRenderer *AmiChat_AmigaRendererCreate(void);
void AmiChat_AmigaRendererDestroy(AmiChatAmigaRenderer *renderer);
void AmiChat_AmigaRendererSetTranscript(AmiChatAmigaRenderer *renderer,const AmiChatTranscript *transcript);
void AmiChat_AmigaRendererDraw(AmiChatAmigaRenderer *renderer,void *window);
void AmiChat_AmigaRendererScroll(AmiChatAmigaRenderer *renderer,int lines);
#ifdef __cplusplus
}
#endif
#endif
