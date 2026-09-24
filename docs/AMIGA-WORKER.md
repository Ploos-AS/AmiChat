# Amiga worker bridge

The Amiga platform worker runs generation outside the Intuition task and delivers stream events through an Exec message port.

The application task waits on the worker port signal together with Intuition, ARexx and Ctrl-C. Worker messages contain copied chunk data, so no provider-owned response buffer is exposed across task boundaries.

This is the first asynchronous plumbing layer. The current implementation uses a single active worker task and therefore intentionally permits only one in-flight generation. The next refinement will replace the bootstrap handoff with explicit task startup state and make cancellation visible to an already-running portable worker.

No GUI code should call the network transport directly once this bridge is integrated.


## Per-task bootstrap

The temporary process-global `active_worker` handoff has been removed. Each worker task now receives its own bootstrap message through a dedicated Exec message port, with the port reference carried in the task's user data. The creator waits only for the bootstrap acknowledgement, not for network completion. This removes cross-job global state and makes task startup deterministic for the single-in-flight worker model.

Cancellation now also reaches the live portable worker instance when it has been created, while an early cancellation flag covers the startup window.
