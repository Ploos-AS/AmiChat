# Conversation presentation model

The transcript model is a portable append-only presentation buffer used while the native UI is receiving streamed output.

It is deliberately separate from persisted conversation history. Conversation objects remain the semantic source of truth; the transcript is a rendering model that can be rebuilt and discarded.

A streamed assistant reply begins a presentation section, appends chunks as they arrive, and is marked finished on DONE. This permits immediate native rendering without mutating the persisted assistant message for every token.

The first renderer is plain text. Richer formatting, selection and Markdown presentation can be layered above this model without changing provider code.


## Reconstruction

The presentation buffer can now be cleared and rebuilt from the semantic AmiChatConversation history. Native front ends can therefore redraw an existing conversation after opening a window, loading a conversation, or replacing the active session conversation. User prompts are also presented immediately before asynchronous generation starts.
