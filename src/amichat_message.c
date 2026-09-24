#include "amichat_internal.h"
#include <stdlib.h>
#include <string.h>
static char *dup_string(const char*s){size_t n;char*p;if(!s)return NULL;n=strlen(s)+1;p=(char*)malloc(n);if(p)memcpy(p,s,n);return p;}
AmiChatMessage *AmiChat_MessageCreate(AmiChatRole role,const char*content){AmiChatMessage*m;if(!content)return NULL;m=(AmiChatMessage*)calloc(1,sizeof(*m));if(!m)return NULL;m->role=role;m->content=dup_string(content);if(!m->content){free(m);return NULL;}return m;}
void AmiChat_MessageFree(AmiChatMessage*m){if(!m)return;free(m->content);free(m);}
AmiChatRole AmiChat_MessageRole(const AmiChatMessage*m){return m?m->role:AMICHAT_ROLE_SYSTEM;}
const char *AmiChat_MessageContent(const AmiChatMessage*m){return m?m->content:NULL;}
AmiChatResult AmiChat_ConversationAppend(AmiChatConversation*c,AmiChatMessage*m){if(!c||!m)return AMICHAT_ERR_INVALID_ARGUMENT;if(m->next)return AMICHAT_ERR_INVALID_ARGUMENT;if(c->tail)c->tail->next=m;else c->head=m;c->tail=m;c->count++;return AMICHAT_OK;}
size_t AmiChat_ConversationMessageCount(const AmiChatConversation*c){return c?c->count:0;}
const AmiChatMessage *AmiChat_ConversationMessageAt(const AmiChatConversation*c,size_t index){const AmiChatMessage*m;if(!c)return NULL;m=c->head;while(m&&index){m=m->next;index--;}return m;}
