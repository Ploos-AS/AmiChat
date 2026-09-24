#include "amichat_transcript.h"
#include <stdlib.h>
#include <string.h>
struct AmiChatTranscript { char *text; size_t length; size_t capacity; int active; AmiChatRole role; };
static AmiChatResult reserve(AmiChatTranscript*t,size_t need){char*p;size_t cap;if(need<=t->capacity)return AMICHAT_OK;cap=t->capacity?t->capacity:256;while(cap<need)cap*=2;p=(char*)realloc(t->text,cap);if(!p)return AMICHAT_ERR_NOMEM;t->text=p;t->capacity=cap;return AMICHAT_OK;}
AmiChatTranscript *AmiChat_TranscriptCreate(void){return(AmiChatTranscript*)calloc(1,sizeof(AmiChatTranscript));}
void AmiChat_TranscriptDestroy(AmiChatTranscript*t){if(!t)return;free(t->text);free(t);}
AmiChatResult AmiChat_TranscriptBegin(AmiChatTranscript*t,AmiChatRole role){const char*label;size_t n;if(!t)return AMICHAT_ERR_INVALID_ARGUMENT;label=role==AMICHAT_ROLE_USER?"You: ":role==AMICHAT_ROLE_ASSISTANT?"Assistant: ":role==AMICHAT_ROLE_SYSTEM?"System: ":"Tool: ";n=strlen(label);if(t->length&&AmiChat_TranscriptAppend(t,"\n\n",2)!=AMICHAT_OK)return AMICHAT_ERR_NOMEM;if(reserve(t,t->length+n+1)!=AMICHAT_OK)return AMICHAT_ERR_NOMEM;memcpy(t->text+t->length,label,n);t->length+=n;t->text[t->length]=0;t->role=role;t->active=1;return AMICHAT_OK;}
AmiChatResult AmiChat_TranscriptAppend(AmiChatTranscript*t,const char*d,size_t n){if(!t||(!d&&n))return AMICHAT_ERR_INVALID_ARGUMENT;if(!n)return AMICHAT_OK;if(reserve(t,t->length+n+1)!=AMICHAT_OK)return AMICHAT_ERR_NOMEM;memcpy(t->text+t->length,d,n);t->length+=n;t->text[t->length]=0;return AMICHAT_OK;}
void AmiChat_TranscriptFinish(AmiChatTranscript*t){if(t)t->active=0;}
void AmiChat_TranscriptClear(AmiChatTranscript*t){if(!t)return;t->length=0;t->active=0;if(t->text)t->text[0]=0;}
AmiChatResult AmiChat_TranscriptRebuild(AmiChatTranscript*t,const AmiChatConversation*c){size_t i,n;const AmiChatMessage*m;const char*text;AmiChatResult r;if(!t||!c)return AMICHAT_ERR_INVALID_ARGUMENT;AmiChat_TranscriptClear(t);n=AmiChat_ConversationMessageCount(c);for(i=0;i<n;i++){m=AmiChat_ConversationMessageAt(c,i);if(!m)continue;r=AmiChat_TranscriptBegin(t,AmiChat_MessageRole(m));if(r!=AMICHAT_OK)return r;text=AmiChat_MessageContent(m);if(text){r=AmiChat_TranscriptAppend(t,text,strlen(text));if(r!=AMICHAT_OK)return r;}AmiChat_TranscriptFinish(t);}return AMICHAT_OK;}
const char *AmiChat_TranscriptText(const AmiChatTranscript*t){return(t&&t->text)?t->text:"";}
size_t AmiChat_TranscriptLength(const AmiChatTranscript*t){return t?t->length:0;}
int AmiChat_TranscriptActive(const AmiChatTranscript*t){return t?t->active:0;}
