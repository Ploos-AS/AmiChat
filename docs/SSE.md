# SSE streaming

AmiChat has an incremental Server-Sent Events parser for OpenAI-compatible streaming.

The parser retains incomplete input between transport callbacks, so an SSE event may be split across arbitrary network reads. Data records are decoded only after an event boundary is available. `[DONE]` completes the AmiChat stream.

The parser deliberately sits above HTTP transport. AmiAPI can therefore feed response-body chunks directly into it without the provider depending on bsdsocket.library or AmiSSL.

Current limits are bounded for classic machines. Oversized buffered events fail rather than growing memory without limit.
