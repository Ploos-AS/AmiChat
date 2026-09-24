# Native Amiga GUI

The first GUI skeleton uses Intuition and GadTools only. There is no MUI dependency.

The main window establishes the initial interaction layout: a conversation/presentation region, prompt string gadget, Send button and Stop button. The window is resizable and exposes its UserPort signal mask for integration with the central Exec event loop.

This is intentionally a skeleton. Sending currently calls the session synchronously; the worker/stream bridge must be added before real network use so the Intuition task remains responsive. Stop is reserved for that asynchronous path.

The presentation region will be implemented as a small native custom layer rather than forcing chat history into unsuitable standard gadgets.
