# AmiAPI transport

AmiChat now has a concrete transport adapter for AmiAPI.

The adapter maps the provider-neutral AmiChat transport interface onto AmiAPI request objects:

- request method and URL
- request headers
- request body
- HTTP status
- response body
- Content-Type

AmiAPI owns the actual HTTP/HTTPS implementation, including the native Amiga transport. AmiChat therefore does not directly depend on bsdsocket.library or AmiSSL.

The adapter intentionally keeps AmiAPI behind the AmiChat transport boundary so host tests can continue using fake transports.

## Streaming

AmiAPI 0.1.2 exposes AmiAPI_RequestSetResponseCallback(), which is the correct integration point for AmiChat's incremental SSE parser. The transport contract now supports an incremental body callback. AmiAPI_RequestSetResponseCallback() feeds chunks directly through that callback, and callback errors propagate back through AmiChat so cancellation or parser failures can stop the request cooperatively.

The next increment connects the OpenAI-compatible adapter's SSE parser directly to this streaming transport path.


## TLS backend boundary

AmiChat depends on AmiAPI for HTTP(S) transport and does not bind its application or provider layers directly to a TLS implementation. The qualified classic-Amiga path currently uses AmiSSL through AmiAPI. AmiSSL is therefore a transport backend dependency, not part of the AmiChat public architecture.

When AmTLS reaches a production-qualified milestone, AmiAPI may add an AmTLS-backed transport while preserving the AmiChat transport contract. This is intended to allow AmiChat to migrate from AmiSSL to AmTLS without provider, conversation, GUI, or ARexx changes.

Until AmTLS is explicitly qualified for security-sensitive HTTPS traffic, AmiSSL remains the production Amiga TLS backend.
