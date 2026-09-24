#include "amichat_openai_compat.h"
#include "amichat_provider.h"
#include <assert.h>
#include <string.h>
typedef struct State { char text[64]; size_t n; } State;
static AmiChatResult fake(AmiChatTransport*t,const AmiChatTransportRequest*r,AmiChatTransportResponse*p){const char*a="data: {\"choices\":[{\"delta\":{\"content\":\"Hel";const char*b="lo\"}}]}\n\ndata: [DONE]\n\n";(void)t;assert(strstr(r->body,"\"stream\":true")!=0);assert(r->body_callback!=0);p->status_code=200;p->body=0;p->content_type="text/event-stream";assert(r->body_callback(a,strlen(a),r->body_userdata)==AMICHAT_OK);assert(r->body_callback(b,strlen(b),r->body_userdata)==AMICHAT_OK);return AMICHAT_OK;}
static int out(const char*d,size_t n,int final,void*u){State*s=(State*)u;if(n){memcpy(s->text+s->n,d,n);s->n+=n;s->text[s->n]='\0';}return final||n?1:1;}
int main(void){static const AmiChatTransportOps ops={fake,0};AmiChatTransport t;AmiChatProvider p;AmiChatOpenAICompatConfig c;AmiChatRequest r;AmiChatStream stream;State s;t.ops=&ops;t.userdata=0;c.base_url="https://example.invalid/v1/chat/completions";c.api_key="test";c.organization=0;assert(AmiChat_OpenAICompat_Init(&p,&t,&c)==AMICHAT_OK);r.model="test";r.system_prompt=0;r.user_prompt="hello";r.stream=&stream;s.text[0]='\0';s.n=0;AmiChat_StreamInit(&stream,out,&s);assert(AmiChat_OpenAICompat_Chat(&p,&r,&stream)==AMICHAT_OK);assert(strcmp(s.text,"Hello")==0);p.ops->destroy(&p);return 0;}
