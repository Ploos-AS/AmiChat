#include "amichat_amiga_renderer.h"
#ifdef __AMIGA__
#include <exec/types.h>
#include <intuition/intuition.h>
#include <graphics/rastport.h>
#include <proto/graphics.h>
#include <stdlib.h>
#include <string.h>
struct AmiChatAmigaRenderer { const AmiChatTranscript *transcript; long scroll; };
AmiChatAmigaRenderer *AmiChat_AmigaRendererCreate(void){return(AmiChatAmigaRenderer*)calloc(1,sizeof(AmiChatAmigaRenderer));}
void AmiChat_AmigaRendererDestroy(AmiChatAmigaRenderer*r){free(r);}
void AmiChat_AmigaRendererSetTranscript(AmiChatAmigaRenderer*r,const AmiChatTranscript*t){if(r)r->transcript=t;}
void AmiChat_AmigaRendererScroll(AmiChatAmigaRenderer*r,int lines){if(!r)return;r->scroll+=lines;if(r->scroll<0)r->scroll=0;}
void AmiChat_AmigaRendererDraw(AmiChatAmigaRenderer*r,void*wp){struct Window*w=(struct Window*)wp;struct RastPort*rp;const char*s,*p,*start;WORD left=10,top=18,right,bottom,y,lineh,width;if(!r||!w||!r->transcript)return;rp=w->RPort;right=w->Width-12;bottom=w->Height-65;lineh=rp->TxHeight+2;width=right-left;SetAPen(rp,0);RectFill(rp,left,top,right,bottom);SetAPen(rp,1);s=AmiChat_TranscriptText(r->transcript);y=top+rp->TxBaseline;start=s;while(*start&&y<=bottom){size_t n=0,best=0;WORD px=0;p=start;if(*p=='\n'){start++;y+=lineh;continue;}while(p[n]&&p[n]!='\n'){px=TextLength(rp,(STRPTR)p,(LONG)(n+1));if(px>width)break;if(p[n]==' '||p[n]=='\t')best=n+1;n++;}if(p[n]&&p[n]!='\n'&&best)n=best;if(!n&&*p)n=1;if(r->scroll>0){r->scroll--;start+=n;while(*start==' ')start++;continue;}Move(rp,left,y);Text(rp,(STRPTR)start,(LONG)n);start+=n;while(*start==' ')start++;if(*start=='\n')start++;y+=lineh;}}
#else
struct AmiChatAmigaRenderer { int unused; };
AmiChatAmigaRenderer *AmiChat_AmigaRendererCreate(void){return 0;}
void AmiChat_AmigaRendererDestroy(AmiChatAmigaRenderer*r){(void)r;}
void AmiChat_AmigaRendererSetTranscript(AmiChatAmigaRenderer*r,const AmiChatTranscript*t){(void)r;(void)t;}
void AmiChat_AmigaRendererDraw(AmiChatAmigaRenderer*r,void*w){(void)r;(void)w;}
void AmiChat_AmigaRendererScroll(AmiChatAmigaRenderer*r,int l){(void)r;(void)l;}
#endif
