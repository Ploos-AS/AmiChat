#include "amichat_stream.h"
void AmiChat_StreamInit(AmiChatStream *s,AmiChatStreamCallback cb,void *u){if(!s)return;s->callback=cb;s->userdata=u;s->cancelled=0;}
void AmiChat_StreamCancel(AmiChatStream *s){if(s)s->cancelled=1;}
int AmiChat_StreamCancelled(const AmiChatStream *s){return s?s->cancelled:1;}
AmiChatResult AmiChat_StreamEmit(AmiChatStream *s,const char *d,size_t n,int f){int keep;if(!s||(!d&&n))return AMICHAT_ERR_INVALID_ARGUMENT;if(s->cancelled)return AMICHAT_ERR_CANCELLED;if(!s->callback)return AMICHAT_OK;keep=s->callback(d,n,f,s->userdata);if(!keep){s->cancelled=1;return AMICHAT_ERR_CANCELLED;}return AMICHAT_OK;}
