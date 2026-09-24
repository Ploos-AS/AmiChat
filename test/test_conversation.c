#include "amichat.h"
#include "amichat_message.h"
#include <assert.h>
#include <string.h>
int main(void){AmiChatContext*ctx=AmiChat_Create();AmiChatConversation*c=AmiChat_NewConversation(ctx);AmiChatMessage*m;assert(ctx&&c);m=AmiChat_MessageCreate(AMICHAT_ROLE_SYSTEM,"Be concise.");assert(m);assert(AmiChat_ConversationAppend(c,m)==AMICHAT_OK);m=AmiChat_MessageCreate(AMICHAT_ROLE_USER,"Hello");assert(AmiChat_ConversationAppend(c,m)==AMICHAT_OK);m=AmiChat_MessageCreate(AMICHAT_ROLE_ASSISTANT,"Hi");assert(AmiChat_ConversationAppend(c,m)==AMICHAT_OK);assert(AmiChat_ConversationMessageCount(c)==3);assert(AmiChat_MessageRole(AmiChat_ConversationMessageAt(c,0))==AMICHAT_ROLE_SYSTEM);assert(strcmp(AmiChat_MessageContent(AmiChat_ConversationMessageAt(c,2)),"Hi")==0);AmiChat_FreeConversation(c);AmiChat_Destroy(ctx);return 0;}
