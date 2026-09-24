# Conversation presentation model

The transcript model is a portable append-only presentation buffer used while the native UI is receiving streamed output.

It is deliberately separate from persisted conversation history. Conversation objects remain the semantic source of truth; the transcript is a rendering model that can be rebuilt and discarded.

A streamed assistant reply begins a presentation section, appends chunks as they arrive, and is marked finished on DONE. This permits immediate native rendering without mutating the persisted assistant message for every token.

The first renderer is plain text. Richer formatting, selection and Markdown presentation can be layered above this model without changing provider code.
