# Provider factory

The provider factory is the runtime bridge between UI/ARexx configuration and protocol adapters.

A caller supplies a provider id plus optional API key, endpoint override and organization. The factory looks up the provider registry and creates the matching adapter.

OpenAI-compatible providers are operational through the shared adapter. Custom OpenAI-compatible endpoints require an explicit endpoint.

Anthropic and Gemini intentionally return `AMICHAT_ERR_UNSUPPORTED` until their native protocol adapters are implemented.

This keeps commands such as `PROVIDER OPENROUTER` independent of HTTP implementation details.
