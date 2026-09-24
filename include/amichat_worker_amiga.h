#ifndef AMICHAT_WORKER_AMIGA_H
#define AMICHAT_WORKER_AMIGA_H
#include "amichat_session.h"
#include "amichat_worker.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatAmigaWorker AmiChatAmigaWorker;
AmiChatAmigaWorker *AmiChat_AmigaWorkerCreate(AmiChatSession *session);
void AmiChat_AmigaWorkerDestroy(AmiChatAmigaWorker *worker);
AmiChatResult AmiChat_AmigaWorkerSend(AmiChatAmigaWorker *worker,const char *prompt);
void AmiChat_AmigaWorkerCancel(AmiChatAmigaWorker *worker);
int AmiChat_AmigaWorkerBusy(const AmiChatAmigaWorker *worker);
unsigned long AmiChat_AmigaWorkerSignalMask(const AmiChatAmigaWorker *worker);
int AmiChat_AmigaWorkerDrain(AmiChatAmigaWorker *worker,AmiChatWorkerEventFn callback,void *userdata);
#ifdef __cplusplus
}
#endif
#endif
