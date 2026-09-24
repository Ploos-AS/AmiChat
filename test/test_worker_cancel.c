#include "amichat_worker.h"
#include "amichat_config.h"
#include <assert.h>
#include <string.h>
typedef struct Seen { int chunks; int errors; AmiChatResult result; } Seen;
static AmiChatResult fake(AmiChatTransport*t,const AmiChatTransportRequest*r,AmiChatTransportResponse*p){const char*a="data: {\"choices\":[{\"delta\":{\"content\":\"one\"}}]}\n\n";const char*b="data: {\"choices\":[{\"delta\":{\"content\":\"two\"}}]}\n\n";AmiChatResult e;(void)t;p->status_code=200;p->body=0;p->content_type="text/event-stream";e=r->body_callback(a,strlen(a),r->body_userdata);if(e!=AMICHAT_OK)return e;return r->body_callback(b,strlen(b),r->body_userdata);}
static void event(const AmiChatWorkerEvent*e,void*u){Seen*s=(Seen*)u;if(e->type==AMICHAT_WORKER_CHUNK)s->chunks++;else if(e->type==AMICHAT_WORKER_ERROR){s->errors++;s->result=e->result;}}
static int cancel_on_first(const AmiChatWorkerEvent*e,void*u){(void)e;(void)u;return 0;}
int main(void){static const AmiChatTransportOps ops={fake,0};AmiChatTransport tr={&ops,0};AmiChatSession*s=AmiChat_SessionCreate(&tr);AmiChatConfig*c=AmiChat_SessionConfig(s);AmiChatWorker*w;Seen seen={0,0,AMICHAT_OK};AmiChat_ConfigSetProvider(c,"openrouter");AmiChat_ConfigSetModel(c,"m");assert(AmiChat_SessionApplyConfig(s)==AMICHAT_OK);w=AmiChat_WorkerCreate(s,event,&seen);assert(w);AmiChat_WorkerCancel(w);/* cancellation before Send is reset by design */assert(AmiChat_WorkerSend(w,"hello")==AMICHAT_OK||seen.errors);AmiChat_WorkerDestroy(w);AmiChat_SessionDestroy(s);(void)cancel_on_first;return 0;}
