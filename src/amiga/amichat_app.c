#include "amichat_amiga_app.h"
#include "amichat_arexx_amiga.h"
#ifdef __AMIGA__
#include <exec/types.h>
#include <proto/exec.h>
#include <stdlib.h>
struct AmiChatAmigaApp { AmiChatSession *session; AmiChatARexxPort *arexx; int quit; ULONG extra_signals; };
AmiChatAmigaApp *AmiChat_AmigaAppCreate(AmiChatSession*s){AmiChatAmigaApp*a;if(!s)return 0;a=(AmiChatAmigaApp*)calloc(1,sizeof(*a));if(!a)return 0;a->session=s;a->arexx=AmiChat_ARexxPortOpen(s);if(!a->arexx){free(a);return 0;}return a;}
void AmiChat_AmigaAppDestroy(AmiChatAmigaApp*a){if(!a)return;AmiChat_ARexxPortClose(a->arexx);free(a);}
void AmiChat_AmigaAppRequestQuit(AmiChatAmigaApp*a){if(a)a->quit=1;}
int AmiChat_AmigaAppRun(AmiChatAmigaApp*a){if(!a)return 0;while(!a->quit){/* Native GUI/network signal masks are added here as their ports become available. */Wait(a->extra_signals|SIGBREAKF_CTRL_C);if(SetSignal(0,0)&SIGBREAKF_CTRL_C)a->quit=1;AmiChat_ARexxPortPoll(a->arexx);}return 1;}
#else
struct AmiChatAmigaApp { AmiChatSession *session; int quit; };
AmiChatAmigaApp *AmiChat_AmigaAppCreate(AmiChatSession*s){(void)s;return 0;}
void AmiChat_AmigaAppDestroy(AmiChatAmigaApp*a){(void)a;}
int AmiChat_AmigaAppRun(AmiChatAmigaApp*a){(void)a;return 0;}
void AmiChat_AmigaAppRequestQuit(AmiChatAmigaApp*a){(void)a;}
#endif
