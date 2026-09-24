#include "amichat_worker_amiga.h"
#ifdef __AMIGA__
#include <exec/types.h>
#include <exec/ports.h>
#include <exec/tasks.h>
#include <proto/exec.h>
#include <stdlib.h>
#include <string.h>

typedef struct WorkerMsg { struct Message msg; AmiChatWorkerEventType type; AmiChatResult result; size_t size; char data[1]; } WorkerMsg;
typedef struct StartMsg { struct Message msg; struct AmiChatAmigaWorker *worker; } StartMsg;

struct AmiChatAmigaWorker {
    AmiChatSession *session;
    struct MsgPort *events;
    struct MsgPort *start;
    struct MsgPort *start_reply;
    struct Task *task;
    AmiChatWorker *core;
    volatile int cancel;
    volatile int busy;
    volatile AmiChatWorkerState state;
    char *prompt;
};

static void emit(const AmiChatWorkerEvent*e,void*u){
    AmiChatAmigaWorker*w=(AmiChatAmigaWorker*)u;WorkerMsg*m;size_t bytes=sizeof(*m)+(e->size?e->size:0);
    m=(WorkerMsg*)AllocMem(bytes,MEMF_PUBLIC|MEMF_CLEAR);if(!m)return;
    m->msg.mn_Length=(UWORD)bytes;m->type=e->type;m->result=e->result;m->size=e->size;
    if(e->size&&e->data)memcpy(m->data,e->data,e->size);
    PutMsg(w->events,(struct Message*)m);
}

static void worker_entry(void){
    struct Task*self=FindTask(NULL);struct MsgPort*start=(struct MsgPort*)self->tc_UserData;StartMsg*m;AmiChatAmigaWorker*w;AmiChatWorkerEvent e;
    if(!start)return;
    WaitPort(start);m=(StartMsg*)GetMsg(start);if(!m)return;w=m->worker;ReplyMsg((struct Message*)m);if(!w)return;
    w->core=AmiChat_WorkerCreate(w->session,emit,w);
    if(w->core){
        AmiChatResult result;
        if(w->cancel)AmiChat_WorkerCancel(w->core);
        result=AmiChat_WorkerSend(w->core,w->prompt);
        w->state=AmiChat_WorkerState(w->core);
        (void)result;
        AmiChat_WorkerDestroy(w->core);w->core=0;
    }else{
        e.type=AMICHAT_WORKER_ERROR;e.data=0;e.size=0;e.result=AMICHAT_ERR_NOMEM;emit(&e,w);
    }
    w->task=0;w->busy=0;
}

AmiChatAmigaWorker *AmiChat_AmigaWorkerCreate(AmiChatSession*s){
    AmiChatAmigaWorker*w;if(!s)return 0;w=(AmiChatAmigaWorker*)calloc(1,sizeof(*w));if(!w)return 0;
    w->session=s;w->state=AMICHAT_WORKER_IDLE;w->events=CreateMsgPort();w->start=CreateMsgPort();w->start_reply=CreateMsgPort();
    if(!w->events||!w->start||!w->start_reply){if(w->events)DeleteMsgPort(w->events);if(w->start)DeleteMsgPort(w->start);if(w->start_reply)DeleteMsgPort(w->start_reply);free(w);return 0;}return w;
}

void AmiChat_AmigaWorkerDestroy(AmiChatAmigaWorker*w){
    WorkerMsg*m;if(!w)return;AmiChat_AmigaWorkerCancel(w);while(w->busy)Delay(1);
    while((m=(WorkerMsg*)GetMsg(w->events))!=0)FreeMem(m,m->msg.mn_Length);
    DeleteMsgPort(w->start_reply);DeleteMsgPort(w->start);DeleteMsgPort(w->events);free(w->prompt);free(w);
}

AmiChatResult AmiChat_AmigaWorkerSend(AmiChatAmigaWorker*w,const char*p){
    size_t n;StartMsg*m;if(!w||!p||!*p)return AMICHAT_ERR_INVALID_ARGUMENT;if(w->busy)return AMICHAT_ERR_UNSUPPORTED;
    n=strlen(p)+1;free(w->prompt);w->prompt=(char*)malloc(n);if(!w->prompt)return AMICHAT_ERR_NOMEM;memcpy(w->prompt,p,n);
    m=(StartMsg*)AllocMem(sizeof(*m),MEMF_PUBLIC|MEMF_CLEAR);
    if(!m)return AMICHAT_ERR_NOMEM;
    m->msg.mn_ReplyPort=w->start_reply;m->msg.mn_Length=sizeof(*m);m->worker=w;
    w->cancel=0;w->busy=1;w->state=AMICHAT_WORKER_GENERATING;
    Forbid();
    w->task=CreateTask((STRPTR)"AmiChat worker",0,worker_entry,32768);
    if(w->task)w->task->tc_UserData=w->start;
    Permit();
    if(!w->task){w->busy=0;w->state=AMICHAT_WORKER_ERROR_STATE;FreeMem(m,sizeof(*m));return AMICHAT_ERR_NOMEM;}
    PutMsg(w->start,(struct Message*)m);
    WaitPort(w->start_reply);GetMsg(w->start_reply);FreeMem(m,sizeof(*m));
    return AMICHAT_OK;
}

void AmiChat_AmigaWorkerCancel(AmiChatAmigaWorker*w){if(!w)return;w->cancel=1;if(w->busy)w->state=AMICHAT_WORKER_CANCELLING;if(w->core)AmiChat_WorkerCancel(w->core);}
int AmiChat_AmigaWorkerBusy(const AmiChatAmigaWorker*w){return w?w->busy:0;}
AmiChatWorkerState AmiChat_AmigaWorkerState(const AmiChatAmigaWorker*w){return w?w->state:AMICHAT_WORKER_ERROR_STATE;}
unsigned long AmiChat_AmigaWorkerSignalMask(const AmiChatAmigaWorker*w){return(w&&w->events)?(1UL<<w->events->mp_SigBit):0;}
int AmiChat_AmigaWorkerDrain(AmiChatAmigaWorker*w,AmiChatWorkerEventFn cb,void*u){WorkerMsg*m;AmiChatWorkerEvent e;int n=0;if(!w)return 0;while((m=(WorkerMsg*)GetMsg(w->events))!=0){n++;e.type=m->type;e.data=m->size?m->data:0;e.size=m->size;e.result=m->result;if(cb)cb(&e,u);FreeMem(m,m->msg.mn_Length);}return n;}
#else
struct AmiChatAmigaWorker { int unused; };
AmiChatAmigaWorker *AmiChat_AmigaWorkerCreate(AmiChatSession*s){(void)s;return 0;}
void AmiChat_AmigaWorkerDestroy(AmiChatAmigaWorker*w){(void)w;}
AmiChatResult AmiChat_AmigaWorkerSend(AmiChatAmigaWorker*w,const char*p){(void)w;(void)p;return AMICHAT_ERR_UNSUPPORTED;}
void AmiChat_AmigaWorkerCancel(AmiChatAmigaWorker*w){(void)w;}
int AmiChat_AmigaWorkerBusy(const AmiChatAmigaWorker*w){(void)w;return 0;}
AmiChatWorkerState AmiChat_AmigaWorkerState(const AmiChatAmigaWorker*w){(void)w;return AMICHAT_WORKER_ERROR_STATE;}
unsigned long AmiChat_AmigaWorkerSignalMask(const AmiChatAmigaWorker*w){(void)w;return 0;}
int AmiChat_AmigaWorkerDrain(AmiChatAmigaWorker*w,AmiChatWorkerEventFn cb,void*u){(void)w;(void)cb;(void)u;return 0;}
#endif
