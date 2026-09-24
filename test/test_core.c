#include "amichat.h"
#include <assert.h>
#include <string.h>

int main(void)
{
    AmiChatContext *ctx = AmiChat_Create();
    AmiChatConversation *conversation;

    assert(ctx != NULL);
    assert(AmiChat_SelectProvider(ctx, "openai-compatible") == AMICHAT_OK);
    assert(AmiChat_SelectModel(ctx, "test-model") == AMICHAT_OK);

    conversation = AmiChat_NewConversation(ctx);
    assert(conversation != NULL);

    assert(AmiChat_Send(ctx, conversation, "hello") == AMICHAT_ERR_UNSUPPORTED);
    assert(strstr(AmiChat_LastError(ctx), "not implemented") != NULL);

    AmiChat_FreeConversation(conversation);
    AmiChat_Destroy(ctx);
    return 0;
}
