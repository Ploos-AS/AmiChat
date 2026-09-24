#include "amichat_worker.h"
#include "amichat_config.h"
#include <assert.h>
#include <string.h>
typedef struct Seen { char text[64]; size_t n; int done; } Seen;
static AmiChatResult fake(AmiChatTransport*t,const AmiChatTransportRequest*r,AmiChatTransportResponse*p){const char*x="data: {\"choices\":[{\"delta\":{\"content\":\"Hi\"}}]}\n\ndata: [DONE]\n\n";(void)t;p->status_code=200;p->body=0;p->content_type="text/event-stream";return r->body_callback(x,strlen(x),r->body_userdata);}
static void event(const AmiChatWorkerEvent*e,void*u){Seen*s=(Seen*)u;if(e->type==AMICHAT_WORKER_CHUNK){memcpy(s->text+s->n,e->data,e->size);s->n+=e->size;s->text[s->n]=0;}else if(e->type==AMICHAT_WORKER_DONE)s->done++;}
int main(void){static const AmiChatTransportOps ops={fake,0};AmiChatTransport t;AmiChatSession*s;AmiChatConfig*c;AmiChatWorker*w;Seen seen={{0},0,0};t.ops=&ops;t.userdata=0;s=AmiChat_SessionCreate(&t);c=AmiChat_SessionConfig(s);AmiChat_ConfigSetProvider(c,"openrouter");AmiChat_ConfigSetModel(c,"m");assert(AmiChat_SessionApplyConfig(s)==AMICHAT_OK);w=AmiChat_WorkerCreate(s,event,&seen);assert(w);assert(AmiChat_WorkerSend(w,"Hello")==AMICHAT_OK);assert(strcmp(seen.text,"Hi")==0);assert(seen.done==1);assert(!AmiChat_WorkerBusy(w));AmiChat_WorkerDestroy(w);AmiChat_SessionDestroy(s);return 0;}
