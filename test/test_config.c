#include "amichat_config.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main(void){AmiChatConfig*c=AmiChat_ConfigCreate();FILE*f;char b[512];size_t n;assert(c);assert(AmiChat_ConfigSetProvider(c,"openrouter")==AMICHAT_OK);assert(AmiChat_ConfigSetModel(c,"model")==AMICHAT_OK);assert(AmiChat_ConfigSetEndpoint(c,"https://example.invalid")==AMICHAT_OK);assert(AmiChat_ConfigSetAPIKey(c,"SECRET-DO-NOT-SAVE")==AMICHAT_OK);assert(strcmp(AmiChat_ConfigAPIKey(c),"SECRET-DO-NOT-SAVE")==0);assert(AmiChat_ConfigSavePublic(c,"test-config.tmp")==AMICHAT_OK);f=fopen("test-config.tmp","r");assert(f);n=fread(b,1,sizeof(b)-1,f);b[n]=0;fclose(f);remove("test-config.tmp");assert(strstr(b,"provider=openrouter")!=0);assert(strstr(b,"SECRET-DO-NOT-SAVE")==0);assert(strstr(b,"api_key")==0);AmiChat_ConfigDestroy(c);return 0;}
