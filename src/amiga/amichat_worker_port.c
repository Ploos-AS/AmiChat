#include "amichat_worker_amiga.h"
#ifdef __AMIGA__
#include <exec/types.h>
#include <exec/ports.h>
#include <exec/tasks.h>
#include <proto/exec.h>
#include <stdlib.h>
#include <string.h>
typedef struct WorkerMsg { struct Message msg; AmiChatWorkerEventType type; AmiChatResult result; size_t size; char data[1]; } WorkerMsg;
struct AmiChatAmigaWorker { AmiChatSession *session; struct MsgPort *events; struct Task *task; volatile int cancel; volatile int busy; char *prompt; };
static AmiChatAmigaWorker *active_worker;
static void emit(const AmiChatWorkerEvent*e,void*u){AmiChatAmigaWorker*w=(AmiChatAmigaWorker*)u;WorkerMsg*m;size_t bytes=sizeof(*m)+(e->size?e->size:0);m=(WorkerMsg*)AllocMem(bytes,MEMF_PUBLIC|MEMF_CLEAR);if(!m)return;m->msg.mn_Length=(UWORD)bytes;m->type=e->type;m->result=e->result;m->size=e->size;if(e->size&&e->data)memcpy(m->data,e->data,e->size);PutMsg(w->events,(struct Message*)m);}
static void worker_entry(void){AmiChatAmigaWorker*w=active_worker;AmiChatWorker*core;AmiChatWorkerEvent e;if(!w)return;core=AmiChat_WorkerCreate(w->session,emit,w);if(core){if(w->cancel)AmiChat_WorkerCancel(core);AmiChat_WorkerSend(core,w->prompt);AmiChat_WorkerDestroy(core);}else{e.type=AMICHAT_WORKER_ERROR;e.data=0;e.size=0;e.result=AMICHAT_ERR_NOMEM;emit(&e,w);}w->busy=0;}
AmiChatAmigaWorker *AmiChat_AmigaWorkerCreate(AmiChatSession*s){AmiChatAmigaWorker*w;if(!s)return 0;w=(AmiChatAmigaWorker*)calloc(1,sizeof(*w));if(!w)return 0;w->session=s;w->events=CreateMsgPort();if(!w->events){free(w);return 0;}return w;}
void AmiChat_AmigaWorkerDestroy(AmiChatAmigaWorker*w){WorkerMsg*m;if(!w)return;while(w->busy)Delay(1);while((m=(WorkerMsg*)GetMsg(w->events))!=0)FreeMem(m,m->msg.mn_Length);DeleteMsgPort(w->events);free(w->prompt);free(w);}
AmiChatResult AmiChat_AmigaWorkerSend(AmiChatAmigaWorker*w,const char*p){size_t n;if(!w||!p||!*p)return AMICHAT_ERR_INVALID_ARGUMENT;if(w->busy)return AMICHAT_ERR_UNSUPPORTED;n=strlen(p)+1;free(w->prompt);w->prompt=(char*)malloc(n);if(!w->prompt)return AMICHAT_ERR_NOMEM;memcpy(w->prompt,p,n);w->cancel=0;w->busy=1;active_worker=w;w->task=CreateTask((STRPTR)"AmiChat worker",0,worker_entry,32768);if(!w->task){w->busy=0;return AMICHAT_ERR_NOMEM;}return AMICHAT_OK;}
void AmiChat_AmigaWorkerCancel(AmiChatAmigaWorker*w){if(w)w->cancel=1;}
unsigned long AmiChat_AmigaWorkerSignalMask(const AmiChatAmigaWorker*w){return(w&&w->events)?(1UL<<w->events->mp_SigBit):0;}
int AmiChat_AmigaWorkerDrain(AmiChatAmigaWorker*w,AmiChatWorkerEventFn cb,void*u){WorkerMsg*m;AmiChatWorkerEvent e;int n=0;if(!w)return 0;while((m=(WorkerMsg*)GetMsg(w->events))!=0){n++;e.type=m->type;e.data=m->size?m->data:0;e.size=m->size;e.result=m->result;if(cb)cb(&e,u);FreeMem(m,m->msg.mn_Length);}return n;}
#else
struct AmiChatAmigaWorker { int unused; };
AmiChatAmigaWorker *AmiChat_AmigaWorkerCreate(AmiChatSession*s){(void)s;return 0;}
void AmiChat_AmigaWorkerDestroy(AmiChatAmigaWorker*w){(void)w;}
AmiChatResult AmiChat_AmigaWorkerSend(AmiChatAmigaWorker*w,const char*p){(void)w;(void)p;return AMICHAT_ERR_UNSUPPORTED;}
void AmiChat_AmigaWorkerCancel(AmiChatAmigaWorker*w){(void)w;}
unsigned long AmiChat_AmigaWorkerSignalMask(const AmiChatAmigaWorker*w){(void)w;return 0;}
int AmiChat_AmigaWorkerDrain(AmiChatAmigaWorker*w,AmiChatWorkerEventFn cb,void*u){(void)w;(void)cb;(void)u;return 0;}
#endif
