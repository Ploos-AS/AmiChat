#ifndef AMICHAT_TRANSPORT_H
#define AMICHAT_TRANSPORT_H

#include "amichat.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AmiChatTransport AmiChatTransport;

typedef struct AmiChatTransportRequest {
    const char *method;
    const char *url;
    const char *headers;
    const char *body;
} AmiChatTransportRequest;

typedef struct AmiChatTransportResponse {
    long status_code;
    const char *body;
    const char *content_type;
} AmiChatTransportResponse;

typedef AmiChatResult (*AmiChatTransportRequestFn)(
    AmiChatTransport *transport,
    const AmiChatTransportRequest *request,
    AmiChatTransportResponse *response);

typedef void (*AmiChatTransportDestroyFn)(AmiChatTransport *transport);

typedef struct AmiChatTransportOps {
    AmiChatTransportRequestFn request;
    AmiChatTransportDestroyFn destroy;
} AmiChatTransportOps;

struct AmiChatTransport {
    const AmiChatTransportOps *ops;
    void *userdata;
};

AmiChatResult AmiChat_TransportRequest(
    AmiChatTransport *transport,
    const AmiChatTransportRequest *request,
    AmiChatTransportResponse *response);

void AmiChat_TransportDestroy(AmiChatTransport *transport);

#ifdef __cplusplus
}
#endif

#endif
