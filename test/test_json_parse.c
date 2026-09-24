#include "amichat_json.h"
#include <assert.h>
#include <string.h>
int main(void){char b[64];assert(AmiChat_JSONFindString("{\"content\":\"hello\\nAmiga\"}","content",b,sizeof(b))!=0);assert(strcmp(b,"hello\nAmiga")==0);return 0;}
