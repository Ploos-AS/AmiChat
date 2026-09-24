#ifndef AMICHAT_INTERNAL_H
#define AMICHAT_INTERNAL_H
#include "amichat.h"
#include "amichat_message.h"
struct AmiChatMessage { AmiChatRole role; char *content; struct AmiChatMessage *next; };
struct AmiChatConversation { char *title; AmiChatMessage *head; AmiChatMessage *tail; size_t count; };
struct AmiChatContext { char *provider_id; char *model_id; char *last_error; };
#endif
