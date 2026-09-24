# Provider registry

AmiChat keeps provider identity separate from wire protocol.

Multiple services use the OpenAI-compatible chat-completions protocol, so they share one adapter while the registry supplies identity, default endpoint and advertised capabilities.

Initial registry entries:

- OpenAI
- OpenRouter
- Groq
- DeepSeek
- Mistral AI
- Together AI
- Fireworks AI
- Ollama
- llama.cpp server
- custom OpenAI-compatible endpoint
- Anthropic
- Google Gemini

Anthropic and Gemini are registered now but require their own protocol adapters before use. A custom endpoint has no compiled-in URL and must be configured by the user.

API keys are configuration data and must never be stored in the provider registry or committed to the repository.
