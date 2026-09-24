#include "amichat_openai_compat.h"
#include "amichat_provider.h"
#include "amichat_message.h"
#include <assert.h>
#include <string.h>
static AmiChatResult fake(AmiChatTransport*t,const AmiChatTransportRequest*r,AmiChatTransportResponse*p){const char*x="data: {\"choices\":[{\"delta\":{\"content\":\"Hello Amiga\"}}]}\n\ndata: [DONE]\n\n";(void)t;p->status_code=200;p->body=0;p->content_type="text/event-stream";return r->body_callback(x,strlen(x),r->body_userdata);}
static int sink(const char*d,size_t n,int f,void*u){(void)d;(void)n;(void)f;(void)u;return 1;}
int main(void){static const AmiChatTransportOps ops={fake,0};AmiChatTransport t;AmiChatProvider p;AmiChatOpenAICompatConfig cfg;AmiChatContext*ctx;AmiChatConversation*c;AmiChatStream s;const AmiChatMessage*m;t.ops=&ops;t.userdata=0;cfg.base_url="https://example.invalid";cfg.api_key=0;cfg.organization=0;assert(AmiChat_OpenAICompat_Init(&p,&t,&cfg)==AMICHAT_OK);ctx=AmiChat_Create();c=AmiChat_NewConversation(ctx);assert(AmiChat_ConversationAppend(c,AmiChat_MessageCreate(AMICHAT_ROLE_USER,"Hi"))==AMICHAT_OK);AmiChat_StreamInit(&s,sink,0);assert(AmiChat_OpenAICompat_Conversation(&p,"model",c,&s)==AMICHAT_OK);assert(AmiChat_ConversationMessageCount(c)==2);m=AmiChat_ConversationMessageAt(c,1);assert(AmiChat_MessageRole(m)==AMICHAT_ROLE_ASSISTANT);assert(strcmp(AmiChat_MessageContent(m),"Hello Amiga")==0);AmiChat_FreeConversation(c);AmiChat_Destroy(ctx);p.ops->destroy(&p);return 0;}
