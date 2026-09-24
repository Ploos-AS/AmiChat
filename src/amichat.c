#include "amichat_internal.h"
#include <stdlib.h>
#include <string.h>
static char *dup_string(const char*s){size_t n;char*p;if(!s)return NULL;n=strlen(s)+1;p=(char*)malloc(n);if(p)memcpy(p,s,n);return p;}
static void set_string(char**dst,const char*src){char*p=dup_string(src);free(*dst);*dst=p;}
AmiChatContext *AmiChat_Create(void){return(AmiChatContext*)calloc(1,sizeof(AmiChatContext));}
void AmiChat_Destroy(AmiChatContext*ctx){if(!ctx)return;free(ctx->provider_id);free(ctx->model_id);free(ctx->last_error);free(ctx);}
AmiChatConversation *AmiChat_NewConversation(AmiChatContext*ctx){AmiChatConversation*c;(void)ctx;c=(AmiChatConversation*)calloc(1,sizeof(*c));if(c)c->title=dup_string("New conversation");return c;}
void AmiChat_FreeConversation(AmiChatConversation*c){AmiChatMessage*m,*next;if(!c)return;m=c->head;while(m){next=m->next;AmiChat_MessageFree(m);m=next;}free(c->title);free(c);}
AmiChatResult AmiChat_SelectProvider(AmiChatContext*ctx,const char*id){if(!ctx||!id||!*id)return AMICHAT_ERR_INVALID_ARGUMENT;set_string(&ctx->provider_id,id);return ctx->provider_id?AMICHAT_OK:AMICHAT_ERR_NOMEM;}
AmiChatResult AmiChat_SelectModel(AmiChatContext*ctx,const char*id){if(!ctx||!id||!*id)return AMICHAT_ERR_INVALID_ARGUMENT;set_string(&ctx->model_id,id);return ctx->model_id?AMICHAT_OK:AMICHAT_ERR_NOMEM;}
AmiChatResult AmiChat_Send(AmiChatContext*ctx,AmiChatConversation*c,const char*prompt){AmiChatMessage*m;if(!ctx||!c||!prompt||!*prompt)return AMICHAT_ERR_INVALID_ARGUMENT;m=AmiChat_MessageCreate(AMICHAT_ROLE_USER,prompt);if(!m)return AMICHAT_ERR_NOMEM;if(AmiChat_ConversationAppend(c,m)!=AMICHAT_OK){AmiChat_MessageFree(m);return AMICHAT_ERR_NOMEM;}set_string(&ctx->last_error,"Provider dispatch not implemented yet");return AMICHAT_ERR_UNSUPPORTED;}
const char *AmiChat_LastError(const AmiChatContext*ctx){return ctx&&ctx->last_error?ctx->last_error:"";}
