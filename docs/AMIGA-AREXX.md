# Native Amiga ARexx port

The Amiga platform layer exposes the portable command dispatcher through the public message port `AMICHAT`.

`AmiChat_ARexxPortOpen()` creates the port, `AmiChat_ARexxPortPoll()` drains pending Rexx messages, dispatches their command strings and replies with standard return/result fields, and `AmiChat_ARexxPortClose()` rejects any remaining queued messages before deleting the port.

The implementation is isolated under `src/amiga/`. Non-Amiga builds receive inert stubs so portable host builds do not require Amiga headers.

The GUI event loop should poll the ARexx port alongside Intuition and application signals. This keeps GUI actions and ARexx automation on the same session and conversation state.


## GUI synchronization

The ARexx public port signal is now part of the application's Wait() mask. After an ARexx command is dispatched, the native GUI rebuilds its presentation transcript from the shared session conversation. Commands such as NEW therefore become visible immediately without requiring unrelated GUI activity to wake the application task.
