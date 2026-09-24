#ifndef AMICHAT_AREXX_AMIGA_H
#define AMICHAT_AREXX_AMIGA_H
#include "amichat_session.h"
#include "amichat_worker_amiga.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatARexxPort AmiChatARexxPort;
AmiChatARexxPort *AmiChat_ARexxPortOpen(AmiChatSession *session,AmiChatAmigaWorker *worker);
void AmiChat_ARexxPortClose(AmiChatARexxPort *port);
int AmiChat_ARexxPortPoll(AmiChatARexxPort *port);
unsigned long AmiChat_ARexxPortSignalMask(const AmiChatARexxPort *port);
#ifdef __cplusplus
}
#endif
#endif
