#include "amichat_transcript.h"
#include <assert.h>
#include <string.h>
int main(void){AmiChatTranscript*t=AmiChat_TranscriptCreate();assert(t);assert(AmiChat_TranscriptBegin(t,AMICHAT_ROLE_USER)==AMICHAT_OK);assert(AmiChat_TranscriptAppend(t,"Hello",5)==AMICHAT_OK);AmiChat_TranscriptFinish(t);assert(AmiChat_TranscriptBegin(t,AMICHAT_ROLE_ASSISTANT)==AMICHAT_OK);assert(AmiChat_TranscriptAppend(t,"Hel",3)==AMICHAT_OK);assert(AmiChat_TranscriptAppend(t,"lo",2)==AMICHAT_OK);assert(strcmp(AmiChat_TranscriptText(t),"You: Hello\n\nAssistant: Hello")==0);assert(AmiChat_TranscriptActive(t));AmiChat_TranscriptFinish(t);assert(!AmiChat_TranscriptActive(t));AmiChat_TranscriptDestroy(t);return 0;}
