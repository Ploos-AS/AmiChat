#include "amichat_amiga_app.h"
#include "amichat_arexx_amiga.h"
#include "amichat_amiga_gui.h"
#include "amichat_worker_amiga.h"
#ifdef __AMIGA__
#include <exec/types.h>
#include <proto/exec.h>
#include <stdlib.h>
struct AmiChatAmigaApp { AmiChatSession *session; AmiChatARexxPort *arexx; AmiChatAmigaWorker *worker; AmiChatAmigaGUI *gui; int quit; };
static void worker_event(const AmiChatWorkerEvent*e,void*u){AmiChatAmigaApp*a=(AmiChatAmigaApp*)u;if(a&&a->gui)AmiChat_AmigaGUIWorkerEvent(a->gui,e);}
AmiChatAmigaApp *AmiChat_AmigaAppCreate(AmiChatSession*s){AmiChatAmigaApp*a;if(!s)return 0;a=(AmiChatAmigaApp*)calloc(1,sizeof(*a));if(!a)return 0;a->session=s;a->worker=AmiChat_AmigaWorkerCreate(s);if(a->worker)a->arexx=AmiChat_ARexxPortOpen(s,a->worker);if(a->worker)a->gui=AmiChat_AmigaGUIOpen(s,a->worker);if(!a->arexx||!a->worker||!a->gui){AmiChat_AmigaAppDestroy(a);return 0;}return a;}
void AmiChat_AmigaAppDestroy(AmiChatAmigaApp*a){if(!a)return;AmiChat_AmigaGUIClose(a->gui);AmiChat_AmigaWorkerDestroy(a->worker);AmiChat_ARexxPortClose(a->arexx);free(a);}
void AmiChat_AmigaAppRequestQuit(AmiChatAmigaApp*a){if(a)a->quit=1;}
int AmiChat_AmigaAppRun(AmiChatAmigaApp*a){ULONG mask,sig;if(!a)return 0;while(!a->quit){mask=AmiChat_AmigaGUISignalMask(a->gui)|AmiChat_AmigaWorkerSignalMask(a->worker)|AmiChat_ARexxPortSignalMask(a->arexx)|SIGBREAKF_CTRL_C;sig=Wait(mask);if(sig&SIGBREAKF_CTRL_C)a->quit=1;if(sig&AmiChat_AmigaGUISignalMask(a->gui))if(AmiChat_AmigaGUIHandle(a->gui))a->quit=1;if(sig&AmiChat_AmigaWorkerSignalMask(a->worker))AmiChat_AmigaWorkerDrain(a->worker,worker_event,a);if(sig&AmiChat_ARexxPortSignalMask(a->arexx)){AmiChat_ARexxPortPoll(a->arexx);AmiChat_AmigaGUIRefreshConversation(a->gui);}}return 1;}
#else
struct AmiChatAmigaApp { AmiChatSession *session; int quit; };
AmiChatAmigaApp *AmiChat_AmigaAppCreate(AmiChatSession*s){(void)s;return 0;}
void AmiChat_AmigaAppDestroy(AmiChatAmigaApp*a){(void)a;}
int AmiChat_AmigaAppRun(AmiChatAmigaApp*a){(void)a;return 0;}
void AmiChat_AmigaAppRequestQuit(AmiChatAmigaApp*a){(void)a;}
#endif
