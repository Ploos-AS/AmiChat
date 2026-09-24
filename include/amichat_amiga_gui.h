#ifndef AMICHAT_AMIGA_GUI_H
#define AMICHAT_AMIGA_GUI_H
#include "amichat_session.h"
#include "amichat_worker_amiga.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatAmigaGUI AmiChatAmigaGUI;
AmiChatAmigaGUI *AmiChat_AmigaGUIOpen(AmiChatSession *session,AmiChatAmigaWorker *worker);
void AmiChat_AmigaGUIClose(AmiChatAmigaGUI *gui);
unsigned long AmiChat_AmigaGUISignalMask(const AmiChatAmigaGUI *gui);
int AmiChat_AmigaGUIHandle(AmiChatAmigaGUI *gui);
#ifdef __cplusplus
}
#endif
#endif
