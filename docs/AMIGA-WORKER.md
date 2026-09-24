# Amiga worker bridge

The Amiga platform worker runs generation outside the Intuition task and delivers stream events through an Exec message port.

The application task waits on the worker port signal together with Intuition, ARexx and Ctrl-C. Worker messages contain copied chunk data, so no provider-owned response buffer is exposed across task boundaries.

This is the first asynchronous plumbing layer. The current implementation uses a single active worker task and therefore intentionally permits only one in-flight generation. The next refinement will replace the bootstrap handoff with explicit task startup state and make cancellation visible to an already-running portable worker.

No GUI code should call the network transport directly once this bridge is integrated.
