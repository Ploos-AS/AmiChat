#include "amichat_arexx_amiga.h"
#include "amichat_arexx.h"
#ifdef __AMIGA__
#include <exec/types.h>
#include <exec/ports.h>
#include <proto/exec.h>
#include <proto/rexxsyslib.h>
#include <rexx/storage.h>
#include <stdlib.h>
#include <string.h>
struct AmiChatARexxPort { struct MsgPort *port; AmiChatSession *session; };
AmiChatARexxPort *AmiChat_ARexxPortOpen(AmiChatSession*s){AmiChatARexxPort*a;if(!s)return 0;a=(AmiChatARexxPort*)calloc(1,sizeof(*a));if(!a)return 0;a->port=CreatePort((STRPTR)AMICHAT_AREXX_PORT,0);if(!a->port){free(a);return 0;}a->session=s;return a;}
void AmiChat_ARexxPortClose(AmiChatARexxPort*a){struct RexxMsg*m;if(!a)return;if(a->port){while((m=(struct RexxMsg*)GetMsg(a->port))!=0){m->rm_Result1=20;m->rm_Result2=0;ReplyMsg((struct Message*)m);}DeletePort(a->port);}free(a);}
unsigned long AmiChat_ARexxPortSignalMask(const AmiChatARexxPort*a){return(a&&a->port)?(1UL<<a->port->mp_SigBit):0;}
int AmiChat_ARexxPortPoll(AmiChatARexxPort*a){struct RexxMsg*m;AmiChatARexxResult r;int n=0;if(!a||!a->port)return 0;while((m=(struct RexxMsg*)GetMsg(a->port))!=0){n++;if(IsRexxMsg(m)&&m->rm_Args[0]){AmiChat_ARexxDispatch(a->session,(const char*)m->rm_Args[0],&r);m->rm_Result1=r.rc;m->rm_Result2=0;if((m->rm_Action&RXFF_RESULT)&&r.result[0])m->rm_Result2=(LONG)CreateArgstring((STRPTR)r.result,(LONG)strlen(r.result));}else{m->rm_Result1=20;m->rm_Result2=0;}ReplyMsg((struct Message*)m);}return n;}
#else
struct AmiChatARexxPort { int unused; };
AmiChatARexxPort *AmiChat_ARexxPortOpen(AmiChatSession*s){(void)s;return 0;}
void AmiChat_ARexxPortClose(AmiChatARexxPort*p){(void)p;}
int AmiChat_ARexxPortPoll(AmiChatARexxPort*p){(void)p;return 0;}
unsigned long AmiChat_ARexxPortSignalMask(const AmiChatARexxPort*p){(void)p;return 0;}
#endif
