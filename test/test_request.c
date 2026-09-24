#include "amichat_request.h"
#include <assert.h>
int main(void){AmiChatRequest r;r.model="test-model";r.system_prompt=0;r.user_prompt="hello";r.stream=0;assert(AmiChat_RequestValidate(&r)==AMICHAT_OK);r.model=0;assert(AmiChat_RequestValidate(&r)==AMICHAT_ERR_INVALID_ARGUMENT);return 0;}
