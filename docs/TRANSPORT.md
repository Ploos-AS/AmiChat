# Transport layer

AmiChat separates provider protocol logic from HTTP transport.

The transport interface is deliberately small:

- request method
- URL
- headers
- request body
- HTTP status
- response body
- content type

The production Amiga transport will be backed by AmiAPI. Host-side tests can use a deterministic fake transport.

Provider adapters must never depend directly on bsdsocket.library, AmiSSL, curl, or another platform-specific HTTP implementation.

## Generic OpenAI-compatible provider

The first provider adapter is intentionally generic. It will support services exposing the common OpenAI-style REST model, allowing many providers and aggregators to work without separate client implementations.

The current M1 increment establishes the provider state and transport boundary. Wire-format generation and response parsing are the next increment.
