#include "amichat_transport.h"

AmiChatResult AmiChat_TransportRequest(
    AmiChatTransport *transport,
    const AmiChatTransportRequest *request,
    AmiChatTransportResponse *response)
{
    if (!transport || !transport->ops || !transport->ops->request ||
        !request || !response)
        return AMICHAT_ERR_INVALID_ARGUMENT;

    return transport->ops->request(transport, request, response);
}

void AmiChat_TransportDestroy(AmiChatTransport *transport)
{
    if (!transport) return;
    if (transport->ops && transport->ops->destroy)
        transport->ops->destroy(transport);
}
