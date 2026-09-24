#ifndef AMICHAT_TRANSPORT_H
#define AMICHAT_TRANSPORT_H
#include "amichat.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AmiChatTransport AmiChatTransport;
typedef AmiChatResult (*AmiChatTransportBodyFn)(const void *,size_t,void *);
typedef struct AmiChatTransportRequest { const char *method; const char *url; const char *headers; const char *body; AmiChatTransportBodyFn body_callback; void *body_userdata; } AmiChatTransportRequest;
typedef struct AmiChatTransportResponse { long status_code; const char *body; const char *content_type; } AmiChatTransportResponse;
typedef AmiChatResult (*AmiChatTransportRequestFn)(AmiChatTransport *,const AmiChatTransportRequest *,AmiChatTransportResponse *);
typedef void (*AmiChatTransportDestroyFn)(AmiChatTransport *);
typedef struct AmiChatTransportOps { AmiChatTransportRequestFn request; AmiChatTransportDestroyFn destroy; } AmiChatTransportOps;
struct AmiChatTransport { const AmiChatTransportOps *ops; void *userdata; };
AmiChatResult AmiChat_TransportRequest(AmiChatTransport *,const AmiChatTransportRequest *,AmiChatTransportResponse *);
void AmiChat_TransportDestroy(AmiChatTransport *);
#ifdef __cplusplus
}
#endif
#endif
