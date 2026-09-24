#include "amichat_transport.h"
AmiChatResult AmiChat_TransportRequest(AmiChatTransport*t,const AmiChatTransportRequest*r,AmiChatTransportResponse*p){if(!t||!t->ops||!t->ops->request||!r||!p)return AMICHAT_ERR_INVALID_ARGUMENT;return t->ops->request(t,r,p);}
void AmiChat_TransportDestroy(AmiChatTransport*t){if(!t)return;if(t->ops&&t->ops->destroy)t->ops->destroy(t);}
