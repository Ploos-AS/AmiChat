#ifndef AMICHAT_JSON_H
#define AMICHAT_JSON_H
#include "amichat.h"
#ifdef __cplusplus
extern "C" {
#endif
AmiChatResult AmiChat_JSONAppendString(char *buffer,size_t capacity,size_t *length,const char *value);
const char *AmiChat_JSONFindString(const char *json,const char *key,char *buffer,size_t capacity);
#ifdef __cplusplus
}
#endif
#endif
