# Worker/stream bridge

The portable worker layer defines the event contract between generation and a user interface: chunk, done and error.

It currently executes synchronously and is therefore a host-testable bridge, not yet the Amiga task implementation. The Amiga platform layer will run this worker from a separate Exec task/process and forward worker events to the application task through an Exec message port.

Cancellation is already represented in the bridge. A cancelled stream callback returns false so provider streaming can abort without committing a completed assistant message.

Keeping the event contract portable lets native Amiga, desktop and test front ends consume the same generation semantics.
