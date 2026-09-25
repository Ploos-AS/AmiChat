#include "amichat_amiga_app.h"
#include "amichat_transport_amiapi.h"
#include "amichat_session.h"

int main(void)
{
    AmiChatTransport *transport;
    AmiChatSession *session;
    AmiChatAmigaApp *app;
    int ok;

    transport = AmiChat_AmiAPITransportCreate();
    if (!transport) return 20;

    session = AmiChat_SessionCreate(transport);
    if (!session) {
        AmiChat_TransportDestroy(transport);
        return 20;
    }

    app = AmiChat_AmigaAppCreate(session);
    if (!app) {
        AmiChat_SessionDestroy(session);
        AmiChat_TransportDestroy(transport);
        return 20;
    }

    ok = AmiChat_AmigaAppRun(app);
    AmiChat_AmigaAppDestroy(app);
    AmiChat_SessionDestroy(session);
    AmiChat_TransportDestroy(transport);
    return ok ? 0 : 20;
}
