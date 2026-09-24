#include "amichat_request.h"
AmiChatResult AmiChat_RequestValidate(const AmiChatRequest *r){if(!r||!r->model||!*r->model||!r->user_prompt)return AMICHAT_ERR_INVALID_ARGUMENT;return AMICHAT_OK;}
