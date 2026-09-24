#ifndef AMICHAT_WORKER_H
#define AMICHAT_WORKER_H
#include "amichat_session.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef enum AmiChatWorkerEventType { AMICHAT_WORKER_CHUNK=1,AMICHAT_WORKER_DONE,AMICHAT_WORKER_ERROR } AmiChatWorkerEventType;
typedef struct AmiChatWorkerEvent { AmiChatWorkerEventType type; const char *data; size_t size; AmiChatResult result; } AmiChatWorkerEvent;
typedef void (*AmiChatWorkerEventFn)(const AmiChatWorkerEvent *event,void *userdata);
typedef struct AmiChatWorker AmiChatWorker;
AmiChatWorker *AmiChat_WorkerCreate(AmiChatSession *session,AmiChatWorkerEventFn callback,void *userdata);
void AmiChat_WorkerDestroy(AmiChatWorker *worker);
AmiChatResult AmiChat_WorkerSend(AmiChatWorker *worker,const char *prompt);
void AmiChat_WorkerCancel(AmiChatWorker *worker);
int AmiChat_WorkerBusy(const AmiChatWorker *worker);
#ifdef __cplusplus
}
#endif
#endif
