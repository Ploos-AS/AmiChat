# AmiChat ARexx Interface

Default ARexx port: AMICHAT

Planned command groups:

- Conversation: NEW, OPEN, CLOSE, LOAD, SAVE, HISTORY, SEARCH
- Provider/model: PROVIDER, MODEL, LISTMODELS, STATUS
- Generation: SEND, REPLY, STREAM, STOP
- Data: ATTACH, EXPORT, PRINT

Commands must be scriptable without GUI interaction. Return codes distinguish syntax, configuration, network, provider and cancellation errors. Text results should be retrievable through standard ARexx result handling where practical. Streaming operations require defined cancellation. The command syntax will be versioned for script compatibility.


## M1 dispatcher

The portable dispatcher now implements `NEW`, `PROVIDER`, `MODEL`, `APPLY`, `SEND` and `STATUS`. It is intentionally independent of Amiga message-port plumbing so the command semantics are host-testable. The native Amiga layer will expose this dispatcher through the `AMICHAT` public ARexx port.
