# AmiChat

A modern, native-first AI chat client for Amiga and other desktop platforms.

## M0 goals

- Native AmigaOS 3.x client
- Modern, polished GUI without requiring MUI
- Portable core for Amiga, Linux, Windows and macOS
- Provider abstraction for major AI services and aggregators
- Generic OpenAI-compatible endpoints
- Local AI backends where practical
- Streaming responses
- Conversation history and search
- Full ARexx integration
- Export and printing as first-class features
- Native Amiga networking through AmiAPI
- No secrets, ROMs or proprietary SDKs in the repository

## Planned providers

OpenAI/ChatGPT, Anthropic/Claude, Google/Gemini, DeepSeek, Mistral, xAI/Grok, Qwen, Perplexity, OpenRouter, Groq, Together AI, Fireworks AI, Ollama, llama.cpp-compatible endpoints and generic OpenAI-compatible APIs.

## Architecture

```text
AmiChat GUI
     |
AmiChat Core ---- ARexx
     |
Provider API
     |
AmiAPI / host transport
     |
HTTP/HTTPS
```

The core is GUI-independent. Provider-specific networking stays in provider adapters.

## GUI

The Amiga GUI is native and modern without a MUI dependency. Intuition, GadTools, BOOPSI and Reaction may be used where appropriate, with a small AmiChat presentation layer where native widgets are insufficient.

## ARexx

ARexx is a first-class automation API. The default port is `AMICHAT`. Conversation control, provider/model selection, generation, streaming, history, export, printing and status are planned for scripting.

## Export and printing

Planned formats include plain text, Markdown, HTML, RTF, PDF, JSON and a native AmiChat conversation format. Native Amiga printing will support complete conversations and selections where practical.

## Networking

AmiChat will use AmiAPI as its Amiga HTTP/HTTPS foundation rather than embedding another HTTP implementation.

## License

MIT. See LICENSE.
