# Amiga event loop

AmiChat uses a single cooperative Amiga event loop rather than a web-style UI loop.

The application object owns platform integration around the shared `AmiChatSession`. The initial skeleton opens the `AMICHAT` ARexx port, handles Ctrl-C shutdown and provides the point where Intuition, application and network/worker signals will be combined into one Exec `Wait()` mask.

The next GUI layer must expose its UserPort signal mask to this loop. Streaming network work should not perform long blocking operations on the UI task; completion/chunk delivery will be signalled back to the application task.

This design keeps the native GUI responsive while preserving ordinary Amiga message-port semantics.
