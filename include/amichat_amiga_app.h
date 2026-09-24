#ifndef AMICHAT_AMIGA_APP_H
#define AMICHAT_AMIGA_APP_H
#include "amichat_session.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatAmigaApp AmiChatAmigaApp;
AmiChatAmigaApp *AmiChat_AmigaAppCreate(AmiChatSession *session);
void AmiChat_AmigaAppDestroy(AmiChatAmigaApp *app);
int AmiChat_AmigaAppRun(AmiChatAmigaApp *app);
void AmiChat_AmigaAppRequestQuit(AmiChatAmigaApp *app);
#ifdef __cplusplus
}
#endif
#endif
