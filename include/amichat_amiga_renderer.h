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
void AmiChat_AmigaRendererFollow(AmiChatAmigaRenderer *renderer,int enabled);
int AmiChat_AmigaRendererFollowing(const AmiChatAmigaRenderer *renderer);
unsigned long AmiChat_AmigaRendererTotalLines(AmiChatAmigaRenderer *renderer,void *window);
unsigned long AmiChat_AmigaRendererVisibleLines(AmiChatAmigaRenderer *renderer,void *window);
unsigned long AmiChat_AmigaRendererTopLine(const AmiChatAmigaRenderer *renderer);
void AmiChat_AmigaRendererSetTopLine(AmiChatAmigaRenderer *renderer,unsigned long line);
#ifdef __cplusplus
}
#endif
#endif
