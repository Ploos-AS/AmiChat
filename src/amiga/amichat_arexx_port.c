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
struct AmiChatARexxPort { struct MsgPort *port; AmiChatSession *session; AmiChatAmigaWorker *worker; };
AmiChatARexxPort *AmiChat_ARexxPortOpen(AmiChatSession*s,AmiChatAmigaWorker*w){AmiChatARexxPort*a;if(!s)return 0;a=(AmiChatARexxPort*)calloc(1,sizeof(*a));if(!a)return 0;a->port=CreatePort((STRPTR)AMICHAT_AREXX_PORT,0);if(!a->port){free(a);return 0;}a->session=s;a->worker=w;return a;}
void AmiChat_ARexxPortClose(AmiChatARexxPort*a){struct RexxMsg*m;if(!a)return;if(a->port){while((m=(struct RexxMsg*)GetMsg(a->port))!=0){m->rm_Result1=20;m->rm_Result2=0;ReplyMsg((struct Message*)m);}DeletePort(a->port);}free(a);}
unsigned long AmiChat_ARexxPortSignalMask(const AmiChatARexxPort*a){return(a&&a->port)?(1UL<<a->port->mp_SigBit):0;}
int AmiChat_ARexxPortPoll(AmiChatARexxPort*a){struct RexxMsg*m;AmiChatARexxResult r;int n=0;if(!a||!a->port)return 0;while((m=(struct RexxMsg*)GetMsg(a->port))!=0){n++;if(IsRexxMsg(m)&&m->rm_Args[0]){{const char*cmd=(const char*)m->rm_Args[0];if(strncmp(cmd,"SEND",4)==0&&(cmd[4]==0||cmd[4]==' '||cmd[4]=='\t')){const char*q=cmd+4;AmiChatResult e;while(*q==' '||*q=='\t')q++;if(!*q){r.rc=10;strcpy(r.result,"SEND REQUIRES TEXT");}else if(!a->worker){r.rc=10;strcpy(r.result,"WORKER UNAVAILABLE");}else{e=AmiChat_AmigaWorkerSend(a->worker,q);if(e==AMICHAT_OK){r.rc=0;strcpy(r.result,"QUEUED");}else{r.rc=10;strcpy(r.result,e==AMICHAT_ERR_UNSUPPORTED?"BUSY":"SEND FAILED");}}}else if(strcmp(cmd,"STOP")==0){if(a->worker){AmiChat_AmigaWorkerCancel(a->worker);r.rc=0;strcpy(r.result,"OK");}else{r.rc=10;strcpy(r.result,"WORKER UNAVAILABLE");}}else if(strcmp(cmd,"BUSY")==0){r.rc=0;strcpy(r.result,(a->worker&&AmiChat_AmigaWorkerBusy(a->worker))?"1":"0");}else AmiChat_ARexxDispatch(a->session,cmd,&r);}m->rm_Result1=r.rc;m->rm_Result2=0;if((m->rm_Action&RXFF_RESULT)&&r.result[0])m->rm_Result2=(LONG)CreateArgstring((STRPTR)r.result,(LONG)strlen(r.result));}else{m->rm_Result1=20;m->rm_Result2=0;}ReplyMsg((struct Message*)m);}return n;}
#else
struct AmiChatARexxPort { int unused; };
AmiChatARexxPort *AmiChat_ARexxPortOpen(AmiChatSession*s,AmiChatAmigaWorker*w){(void)s;(void)w;return 0;}
void AmiChat_ARexxPortClose(AmiChatARexxPort*p){(void)p;}
int AmiChat_ARexxPortPoll(AmiChatARexxPort*p){(void)p;return 0;}
unsigned long AmiChat_ARexxPortSignalMask(const AmiChatARexxPort*p){(void)p;return 0;}
#endif
