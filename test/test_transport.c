#include "amichat_transport.h"
#include <assert.h>
#include <string.h>

static AmiChatResult fake_request(
    AmiChatTransport *transport,
    const AmiChatTransportRequest *request,
    AmiChatTransportResponse *response)
{
    (void)transport;
    assert(request != NULL);
    assert(response != NULL);
    assert(strcmp(request->method, "GET") == 0);
    response->status_code = 200;
    response->body = "ok";
    response->content_type = "text/plain";
    return AMICHAT_OK;
}

static const AmiChatTransportOps ops = {
    fake_request,
    0
};

int main(void)
{
    AmiChatTransport transport;
    AmiChatTransportRequest request;
    AmiChatTransportResponse response;

    transport.ops = &ops;
    transport.userdata = 0;
    request.method = "GET";
    request.url = "https://example.invalid/";
    request.headers = 0;
    request.body = 0;
    request.body_callback = 0;
    request.body_userdata = 0;

    assert(AmiChat_TransportRequest(&transport, &request, &response) == AMICHAT_OK);
    assert(response.status_code == 200);
    assert(strcmp(response.body, "ok") == 0);
    return 0;
}
