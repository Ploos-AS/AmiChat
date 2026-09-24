# AmiChat Architecture

## Principles

1. Core first.
2. Provider-neutral conversation model.
3. Native Amiga GUI without a MUI dependency.
4. ARexx is a first-class automation API.
5. Export and printing use the same conversation model as the GUI.
6. Amiga HTTP/HTTPS transport is provided by AmiAPI.
7. Host-side testing must be possible without Amiga hardware.
8. Provider credentials never belong in source control.

## Layers

- Core: conversations, messages, roles, provider/model metadata, streaming, cancellation, errors, history and capabilities.
- Provider API: common interface with provider-specific wire formats isolated in adapters.
- Transport: AmiAPI on Amiga; host transport for POSIX testing.
- Presentation: GUI consumes core events and submits core commands.
- Automation: ARexx maps stable commands onto core operations.
- Export/Print: common conversation/document representation.

## Initial provider strategy

1. Generic OpenAI-compatible provider
2. OpenAI
3. Anthropic
4. Google/Gemini
5. DeepSeek
6. Aggregators
7. Local model backends

## M0 boundary

M0 establishes interfaces and architectural constraints. Provider implementations, GUI widgets, ARexx runtime, export encoders, printing and persistence are subsequent milestones.
