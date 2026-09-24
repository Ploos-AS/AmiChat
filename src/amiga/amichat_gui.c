#include "amichat_amiga_gui.h"
#include "amichat_transcript.h"
#ifdef __AMIGA__
#include <exec/types.h>
#include <intuition/intuition.h>
#include <libraries/gadtools.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include <proto/gadtools.h>
#include <stdlib.h>
enum { GID_PROMPT=1,GID_SEND,GID_STOP };
struct AmiChatAmigaGUI { AmiChatSession *session; AmiChatAmigaWorker *worker; AmiChatTranscript *transcript; struct Window *window; struct Gadget *gadgets; struct Gadget *prompt; void *visual; };
AmiChatAmigaGUI *AmiChat_AmigaGUIOpen(AmiChatSession*s,AmiChatAmigaWorker*w){AmiChatAmigaGUI*g;struct Gadget*last=0;struct NewGadget ng;if(!s)return 0;g=(AmiChatAmigaGUI*)calloc(1,sizeof(*g));if(!g)return 0;g->session=s;g->worker=w;g->transcript=AmiChat_TranscriptCreate();if(!g->transcript){free(g);return 0;}g->visual=GetVisualInfoA(NULL,NULL);if(!g->visual){free(g);return 0;}last=CreateContext(&g->gadgets);ng.ng_VisualInfo=g->visual;ng.ng_TextAttr=0;ng.ng_Flags=PLACETEXT_IN;ng.ng_LeftEdge=10;ng.ng_TopEdge=150;ng.ng_Width=430;ng.ng_Height=18;ng.ng_GadgetText=(STRPTR)"Prompt:";ng.ng_GadgetID=GID_PROMPT;ng.ng_UserData=0;g->prompt=CreateGadget(STRING_KIND,last,&ng,GTST_MaxChars,1024,TAG_DONE);last=g->prompt;ng.ng_LeftEdge=450;ng.ng_Width=60;ng.ng_GadgetText=(STRPTR)"Send";ng.ng_GadgetID=GID_SEND;last=CreateGadget(BUTTON_KIND,last,&ng,TAG_DONE);ng.ng_LeftEdge=515;ng.ng_GadgetText=(STRPTR)"Stop";ng.ng_GadgetID=GID_STOP;last=CreateGadget(BUTTON_KIND,last,&ng,TAG_DONE);g->window=OpenWindowTags(NULL,WA_Title,(ULONG)"AmiChat",WA_Left,20,WA_Top,20,WA_Width,590,WA_Height,210,WA_MinWidth,400,WA_MinHeight,180,WA_MaxWidth,-1,WA_MaxHeight,-1,WA_DragBar,TRUE,WA_DepthGadget,TRUE,WA_CloseGadget,TRUE,WA_SizeGadget,TRUE,WA_Activate,TRUE,WA_Gadgets,(ULONG)g->gadgets,WA_IDCMP,IDCMP_CLOSEWINDOW|IDCMP_GADGETUP|IDCMP_NEWSIZE,TAG_DONE);if(!g->window){AmiChat_AmigaGUIClose(g);return 0;}GT_RefreshWindow(g->window,NULL);return g;}
void AmiChat_AmigaGUIClose(AmiChatAmigaGUI*g){if(!g)return;if(g->window)CloseWindow(g->window);if(g->gadgets)FreeGadgets(g->gadgets);if(g->visual)FreeVisualInfo(g->visual);AmiChat_TranscriptDestroy(g->transcript);free(g);}
unsigned long AmiChat_AmigaGUISignalMask(const AmiChatAmigaGUI*g){return(g&&g->window)?(1UL<<g->window->UserPort->mp_SigBit):0;}
int AmiChat_AmigaGUIHandle(AmiChatAmigaGUI*g){struct IntuiMessage*m;ULONG cls;UWORD code;struct Gadget*gad;int quit=0;if(!g||!g->window)return 0;while((m=GT_GetIMsg(g->window->UserPort))!=0){cls=m->Class;code=m->Code;gad=(struct Gadget*)m->IAddress;GT_ReplyIMsg(m);(void)code;if(cls==IDCMP_CLOSEWINDOW)quit=1;else if(cls==IDCMP_GADGETUP&&gad&&gad->GadgetID==GID_SEND){struct StringInfo*si=(struct StringInfo*)g->prompt->SpecialInfo;if(si&&si->Buffer&&*si->Buffer&&g->worker)AmiChat_AmigaWorkerSend(g->worker,si->Buffer);}else if(cls==IDCMP_GADGETUP&&gad&&gad->GadgetID==GID_STOP&&g->worker)AmiChat_AmigaWorkerCancel(g->worker);}return quit;}
void AmiChat_AmigaGUIWorkerEvent(AmiChatAmigaGUI*g,const AmiChatWorkerEvent*e){if(!g||!e)return;if(e->type==AMICHAT_WORKER_CHUNK){if(!AmiChat_TranscriptActive(g->transcript))AmiChat_TranscriptBegin(g->transcript,AMICHAT_ROLE_ASSISTANT);AmiChat_TranscriptAppend(g->transcript,e->data,e->size);/* renderer invalidation follows */}else if(e->type==AMICHAT_WORKER_DONE||e->type==AMICHAT_WORKER_ERROR)AmiChat_TranscriptFinish(g->transcript);}
#else
struct AmiChatAmigaGUI { int unused; };
AmiChatAmigaGUI *AmiChat_AmigaGUIOpen(AmiChatSession*s,AmiChatAmigaWorker*w){(void)s;(void)w;return 0;}
void AmiChat_AmigaGUIClose(AmiChatAmigaGUI*g){(void)g;}
unsigned long AmiChat_AmigaGUISignalMask(const AmiChatAmigaGUI*g){(void)g;return 0;}
int AmiChat_AmigaGUIHandle(AmiChatAmigaGUI*g){(void)g;return 0;}
void AmiChat_AmigaGUIWorkerEvent(AmiChatAmigaGUI*g,const AmiChatWorkerEvent*e){(void)g;(void)e;}
#endif
