# Streaming

AmiChat streaming is provider-neutral.

Provider adapters emit decoded text segments through AmiChatStream. GUI, ARexx and exporters consume the core stream rather than provider-specific wire formats.

A callback returning zero requests cooperative cancellation.

The Amiga implementation will map provider streaming onto AmiAPI incremental response-body callbacks. The parser must handle transport chunks that split JSON/SSE records across boundaries; a network read is never assumed to equal one logical event.
