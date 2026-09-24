# Amiga event loop

AmiChat uses a single cooperative Amiga event loop rather than a web-style UI loop.

The application object owns platform integration around the shared `AmiChatSession`. The initial skeleton opens the `AMICHAT` ARexx port, handles Ctrl-C shutdown and provides the point where Intuition, application and network/worker signals will be combined into one Exec `Wait()` mask.

The next GUI layer must expose its UserPort signal mask to this loop. Streaming network work should not perform long blocking operations on the UI task; completion/chunk delivery will be signalled back to the application task.

This design keeps the native GUI responsive while preserving ordinary Amiga message-port semantics.


## Integrated loop

The application now waits on the GUI UserPort and worker event port together with Ctrl-C, drains worker stream events on the application task, and routes Send/Stop through the asynchronous worker bridge. ARexx dispatch remains serviced from the same application loop. The next presentation-layer step will render worker chunks instead of discarding them.


## Generation state UI

The GadTools window now exposes the shared generation state in a native text gadget. Send is disabled while generation is active or cancellation is pending; Stop is enabled only while actively generating. Worker completion, cancellation, and errors resynchronize the controls with the shared worker state.
