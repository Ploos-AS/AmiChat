#include "amichat_registry.h"
#include "amichat_provider.h"
#include <string.h>
static const AmiChatProviderDefinition providers[]={
{"openai","OpenAI",AMICHAT_PROTOCOL_OPENAI_COMPAT,"https://api.openai.com/v1/chat/completions",AMICHAT_CAP_STREAMING|AMICHAT_CAP_VISION|AMICHAT_CAP_TOOLS},
{"openrouter","OpenRouter",AMICHAT_PROTOCOL_OPENAI_COMPAT,"https://openrouter.ai/api/v1/chat/completions",AMICHAT_CAP_STREAMING|AMICHAT_CAP_VISION|AMICHAT_CAP_TOOLS},
{"groq","Groq",AMICHAT_PROTOCOL_OPENAI_COMPAT,"https://api.groq.com/openai/v1/chat/completions",AMICHAT_CAP_STREAMING},
{"deepseek","DeepSeek",AMICHAT_PROTOCOL_OPENAI_COMPAT,"https://api.deepseek.com/chat/completions",AMICHAT_CAP_STREAMING|AMICHAT_CAP_REASONING},
{"mistral","Mistral AI",AMICHAT_PROTOCOL_OPENAI_COMPAT,"https://api.mistral.ai/v1/chat/completions",AMICHAT_CAP_STREAMING},
{"together","Together AI",AMICHAT_PROTOCOL_OPENAI_COMPAT,"https://api.together.xyz/v1/chat/completions",AMICHAT_CAP_STREAMING},
{"fireworks","Fireworks AI",AMICHAT_PROTOCOL_OPENAI_COMPAT,"https://api.fireworks.ai/inference/v1/chat/completions",AMICHAT_CAP_STREAMING},
{"ollama","Ollama",AMICHAT_PROTOCOL_OPENAI_COMPAT,"http://127.0.0.1:11434/v1/chat/completions",AMICHAT_CAP_STREAMING},
{"llamacpp","llama.cpp server",AMICHAT_PROTOCOL_OPENAI_COMPAT,"http://127.0.0.1:8080/v1/chat/completions",AMICHAT_CAP_STREAMING},
{"custom","Custom OpenAI-compatible",AMICHAT_PROTOCOL_OPENAI_COMPAT,0,AMICHAT_CAP_STREAMING},
{"anthropic","Anthropic",AMICHAT_PROTOCOL_ANTHROPIC,"https://api.anthropic.com/v1/messages",AMICHAT_CAP_STREAMING|AMICHAT_CAP_VISION|AMICHAT_CAP_TOOLS},
{"gemini","Google Gemini",AMICHAT_PROTOCOL_GEMINI,0,AMICHAT_CAP_STREAMING|AMICHAT_CAP_VISION|AMICHAT_CAP_TOOLS}
};
size_t AmiChat_ProviderDefinitionCount(void){return sizeof(providers)/sizeof(providers[0]);}
const AmiChatProviderDefinition *AmiChat_ProviderDefinitionAt(size_t i){return i<AmiChat_ProviderDefinitionCount()?&providers[i]:0;}
const AmiChatProviderDefinition *AmiChat_ProviderDefinitionFind(const char*id){size_t i;if(!id)return 0;for(i=0;i<AmiChat_ProviderDefinitionCount();i++)if(strcmp(providers[i].id,id)==0)return &providers[i];return 0;}
