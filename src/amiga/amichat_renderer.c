#include "amichat_amiga_renderer.h"
#ifdef __AMIGA__
#include <exec/types.h>
#include <intuition/intuition.h>
#include <graphics/rastport.h>
#include <proto/graphics.h>
#include <stdlib.h>
#include <string.h>

struct AmiChatAmigaRenderer { const AmiChatTranscript *transcript; long scroll; int follow; };

static const char *next_visual_line(struct RastPort*rp,const char*s,WORD width,size_t*n){
    size_t len=0,best=0;if(!s||!*s){*n=0;return s;}
    if(*s=='\n'){*n=0;return s+1;}
    while(s[len]&&s[len]!='\n'){
        if(TextLength(rp,(STRPTR)s,(LONG)(len+1))>width)break;
        if(s[len]==' '||s[len]=='\t')best=len+1;
        len++;
    }
    if(s[len]&&s[len]!='\n'&&best)len=best;
    if(!len)len=1;*n=len;s+=len;
    while(*s==' ')s++;
    if(*s=='\n')s++;
    return s;
}

AmiChatAmigaRenderer *AmiChat_AmigaRendererCreate(void){AmiChatAmigaRenderer*r=(AmiChatAmigaRenderer*)calloc(1,sizeof(*r));if(r)r->follow=1;return r;}
void AmiChat_AmigaRendererDestroy(AmiChatAmigaRenderer*r){free(r);}
void AmiChat_AmigaRendererSetTranscript(AmiChatAmigaRenderer*r,const AmiChatTranscript*t){if(r)r->transcript=t;}
void AmiChat_AmigaRendererScroll(AmiChatAmigaRenderer*r,int lines){if(!r)return;r->scroll+=lines;if(r->scroll<0)r->scroll=0;r->follow=0;}
void AmiChat_AmigaRendererFollow(AmiChatAmigaRenderer*r,int enabled){if(r)r->follow=enabled?1:0;}
int AmiChat_AmigaRendererFollowing(const AmiChatAmigaRenderer*r){return r?r->follow:0;}
unsigned long AmiChat_AmigaRendererVisibleLines(AmiChatAmigaRenderer*r,void*wp){struct Window*w=(struct Window*)wp;long h,lineh;(void)r;if(!w||!w->RPort)return 0;h=(long)w->Height-65-18+1;lineh=w->RPort->TxHeight+2;return lineh>0?(unsigned long)(h/lineh):0;}
unsigned long AmiChat_AmigaRendererTotalLines(AmiChatAmigaRenderer*r,void*wp){struct Window*w=(struct Window*)wp;const char*s;size_t n;WORD width;unsigned long lines=0;if(!r||!w||!w->RPort||!r->transcript)return 0;width=w->Width-47;s=AmiChat_TranscriptText(r->transcript);while(s&&*s){s=next_visual_line(w->RPort,s,width,&n);lines++;}return lines;}
unsigned long AmiChat_AmigaRendererTopLine(const AmiChatAmigaRenderer*r){return r&&r->scroll>0?(unsigned long)r->scroll:0;}
void AmiChat_AmigaRendererSetTopLine(AmiChatAmigaRenderer*r,unsigned long line){if(r){r->scroll=(long)line;r->follow=0;}}

void AmiChat_AmigaRendererDraw(AmiChatAmigaRenderer*r,void*wp){
    struct Window*w=(struct Window*)wp;struct RastPort*rp;const char*s,*next;size_t n;unsigned long skip;
    WORD left=10,top=18,right,bottom,y,lineh,width;
    if(!r||!w||!w->RPort||!r->transcript)return;rp=w->RPort;right=w->Width-37;bottom=w->Height-65;lineh=rp->TxHeight+2;width=right-left;
    SetAPen(rp,0);RectFill(rp,left,top,right,bottom);SetAPen(rp,1);
    s=AmiChat_TranscriptText(r->transcript);skip=r->scroll;
    while(s&&*s&&skip){s=next_visual_line(rp,s,width,&n);skip--;}
    y=top+rp->TxBaseline;
    while(s&&*s&&y<=bottom){
        next=next_visual_line(rp,s,width,&n);
        if(n){Move(rp,left,y);Text(rp,(STRPTR)s,(LONG)n);}
        s=next;y+=lineh;
    }
}
#else
struct AmiChatAmigaRenderer { int unused; };
AmiChatAmigaRenderer *AmiChat_AmigaRendererCreate(void){return 0;}
void AmiChat_AmigaRendererDestroy(AmiChatAmigaRenderer*r){(void)r;}
void AmiChat_AmigaRendererSetTranscript(AmiChatAmigaRenderer*r,const AmiChatTranscript*t){(void)r;(void)t;}
void AmiChat_AmigaRendererDraw(AmiChatAmigaRenderer*r,void*w){(void)r;(void)w;}
void AmiChat_AmigaRendererScroll(AmiChatAmigaRenderer*r,int l){(void)r;(void)l;}
void AmiChat_AmigaRendererFollow(AmiChatAmigaRenderer*r,int e){(void)r;(void)e;}
int AmiChat_AmigaRendererFollowing(const AmiChatAmigaRenderer*r){(void)r;return 0;}
unsigned long AmiChat_AmigaRendererTotalLines(AmiChatAmigaRenderer*r,void*w){(void)r;(void)w;return 0;}
unsigned long AmiChat_AmigaRendererVisibleLines(AmiChatAmigaRenderer*r,void*w){(void)r;(void)w;return 0;}
unsigned long AmiChat_AmigaRendererTopLine(const AmiChatAmigaRenderer*r){(void)r;return 0;}
void AmiChat_AmigaRendererSetTopLine(AmiChatAmigaRenderer*r,unsigned long l){(void)r;(void)l;}
#endif
