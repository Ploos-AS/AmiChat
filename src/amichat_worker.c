#include "amichat_worker.h"
#include "amichat_stream.h"
#include <stdlib.h>
struct AmiChatWorker { AmiChatSession *session; AmiChatWorkerEventFn callback; void *userdata; int busy; int cancelled; AmiChatStream *active_stream; };
static int stream_cb(const char*d,size_t n,int final,void*u){AmiChatWorker*w=(AmiChatWorker*)u;AmiChatWorkerEvent e;if(w->cancelled)return 0;if(n){e.type=AMICHAT_WORKER_CHUNK;e.data=d;e.size=n;e.result=AMICHAT_OK;if(w->callback)w->callback(&e,w->userdata);}if(final){e.type=AMICHAT_WORKER_DONE;e.data=0;e.size=0;e.result=AMICHAT_OK;if(w->callback)w->callback(&e,w->userdata);}return 1;}
AmiChatWorker *AmiChat_WorkerCreate(AmiChatSession*s,AmiChatWorkerEventFn cb,void*u){AmiChatWorker*w;if(!s)return 0;w=(AmiChatWorker*)calloc(1,sizeof(*w));if(!w)return 0;w->session=s;w->callback=cb;w->userdata=u;return w;}
void AmiChat_WorkerDestroy(AmiChatWorker*w){free(w);}
AmiChatResult AmiChat_WorkerSend(AmiChatWorker*w,const char*p){AmiChatStream s;AmiChatResult r;AmiChatWorkerEvent e;if(!w||!p)return AMICHAT_ERR_INVALID_ARGUMENT;if(w->busy)return AMICHAT_ERR_UNSUPPORTED;w->busy=1;w->cancelled=0;AmiChat_StreamInit(&s,stream_cb,w);w->active_stream=&s;r=AmiChat_SessionSend(w->session,p,&s);w->active_stream=0;if(w->cancelled||r==AMICHAT_ERR_CANCELLED)r=AMICHAT_ERR_CANCELLED;if(r!=AMICHAT_OK&&w->callback){e.type=(r==AMICHAT_ERR_CANCELLED)?AMICHAT_WORKER_CANCELLED:AMICHAT_WORKER_ERROR;e.data=0;e.size=0;e.result=r;w->callback(&e,w->userdata);}w->busy=0;return r;}
void AmiChat_WorkerCancel(AmiChatWorker*w){if(!w)return;w->cancelled=1;if(w->active_stream)AmiChat_StreamCancel(w->active_stream);}
int AmiChat_WorkerBusy(const AmiChatWorker*w){return w?w->busy:0;}
