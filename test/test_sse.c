#include "amichat_sse.h"
#include <assert.h>
#include <string.h>
typedef struct State { char text[64]; size_t length; int final; } State;
static int cb(const char*d,size_t n,int f,void*u){State*s=(State*)u;if(n){memcpy(s->text+s->length,d,n);s->length+=n;s->text[s->length]='\0';}if(f)s->final=1;return 1;}
int main(void){AmiChatSSEParser p;AmiChatStream stream;State s;s.text[0]='\0';s.length=0;s.final=0;AmiChat_StreamInit(&stream,cb,&s);AmiChat_SSEInit(&p,&stream);assert(AmiChat_SSEFeed(&p,"data: {\"delta\":{\"content\":\"Hel",37)==AMICHAT_OK);assert(AmiChat_SSEFeed(&p,"lo\"}}\n\ndata: {\"delta\":{\"content\":\" Amiga\"}}\n\ndata: [DONE]\n\n",65)==AMICHAT_OK);assert(strcmp(s.text,"Hello Amiga")==0);assert(s.final==1);return 0;}
