#include "amichat_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct AmiChatConfig { char *provider; char *model; char *endpoint; char *api_key; };
static char *copy(const char*s){size_t n;char*p;if(!s)return 0;n=strlen(s)+1;p=(char*)malloc(n);if(p)memcpy(p,s,n);return p;}
static AmiChatResult set(char**dst,const char*s){char*p;if(!s)return AMICHAT_ERR_INVALID_ARGUMENT;p=copy(s);if(!p)return AMICHAT_ERR_NOMEM;free(*dst);*dst=p;return AMICHAT_OK;}
static void wipe(char*s){volatile char*p=(volatile char*)s;if(!s)return;while(*p){*p=0;p++;}}
AmiChatConfig *AmiChat_ConfigCreate(void){return(AmiChatConfig*)calloc(1,sizeof(AmiChatConfig));}
void AmiChat_ConfigDestroy(AmiChatConfig*c){if(!c)return;free(c->provider);free(c->model);free(c->endpoint);if(c->api_key){wipe(c->api_key);free(c->api_key);}free(c);}
AmiChatResult AmiChat_ConfigSetProvider(AmiChatConfig*c,const char*v){return c?set(&c->provider,v):AMICHAT_ERR_INVALID_ARGUMENT;}
AmiChatResult AmiChat_ConfigSetModel(AmiChatConfig*c,const char*v){return c?set(&c->model,v):AMICHAT_ERR_INVALID_ARGUMENT;}
AmiChatResult AmiChat_ConfigSetEndpoint(AmiChatConfig*c,const char*v){return c?set(&c->endpoint,v):AMICHAT_ERR_INVALID_ARGUMENT;}
AmiChatResult AmiChat_ConfigSetAPIKey(AmiChatConfig*c,const char*v){AmiChatResult r;if(!c)return AMICHAT_ERR_INVALID_ARGUMENT;if(c->api_key)wipe(c->api_key);r=set(&c->api_key,v);return r;}
const char *AmiChat_ConfigProvider(const AmiChatConfig*c){return c?c->provider:0;}
const char *AmiChat_ConfigModel(const AmiChatConfig*c){return c?c->model:0;}
const char *AmiChat_ConfigEndpoint(const AmiChatConfig*c){return c?c->endpoint:0;}
const char *AmiChat_ConfigAPIKey(const AmiChatConfig*c){return c?c->api_key:0;}
AmiChatResult AmiChat_ConfigSavePublic(const AmiChatConfig*c,const char*path){FILE*f;if(!c||!path)return AMICHAT_ERR_INVALID_ARGUMENT;f=fopen(path,"w");if(!f)return AMICHAT_ERR_PROVIDER;if(c->provider)fprintf(f,"provider=%s\n",c->provider);if(c->model)fprintf(f,"model=%s\n",c->model);if(c->endpoint)fprintf(f,"endpoint=%s\n",c->endpoint);if(fclose(f)!=0)return AMICHAT_ERR_PROVIDER;return AMICHAT_OK;}
