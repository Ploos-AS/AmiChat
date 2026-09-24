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

AmiAPI 0.1.2 exposes AmiAPI_RequestSetResponseCallback(), which is the correct integration point for AmiChat's incremental SSE parser. The next increment extends the AmiChat transport contract with a streaming body callback rather than buffering the complete response.
