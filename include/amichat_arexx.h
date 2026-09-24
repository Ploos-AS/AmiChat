#ifndef AMICHAT_AREXX_H
#define AMICHAT_AREXX_H
#include "amichat_session.h"
#ifdef __cplusplus
extern "C" {
#endif
#define AMICHAT_AREXX_PORT "AMICHAT"
typedef struct AmiChatARexxResult { int rc; char result[512]; } AmiChatARexxResult;
AmiChatResult AmiChat_ARexxDispatch(AmiChatSession *session,const char *command,AmiChatARexxResult *result);
#ifdef __cplusplus
}
#endif
#endif
