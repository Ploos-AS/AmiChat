#include "amichat_json.h"
#include <assert.h>
#include <string.h>

int main(void)
{
    char buffer[128];
    size_t length = 0;

    buffer[0] = '\0';
    assert(AmiChat_JSONAppendString(buffer, sizeof(buffer), &length,
                                    "hello \"Amiga\"\n") == AMICHAT_OK);
    assert(strcmp(buffer, "\"hello \\\"Amiga\\\"\\n\"") == 0);
    return 0;
}
