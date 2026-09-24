# OpenAI-compatible provider

The first wire-format adapter targets the common chat-completions shape used by many providers and aggregators.

The adapter owns request construction and response extraction. The transport owns HTTP. AmiChat core owns conversations and streaming callbacks.

This increment provides a bounded request/response path for deterministic host tests. Production streaming still requires an incremental SSE parser and an AmiAPI body callback; that is the next transport increment.
