# AmiChat ARexx Interface

Default ARexx port: AMICHAT

Planned command groups:

- Conversation: NEW, OPEN, CLOSE, LOAD, SAVE, HISTORY, SEARCH
- Provider/model: PROVIDER, MODEL, LISTMODELS, STATUS
- Generation: SEND, REPLY, STREAM, STOP
- Data: ATTACH, EXPORT, PRINT

Commands must be scriptable without GUI interaction. Return codes distinguish syntax, configuration, network, provider and cancellation errors. Text results should be retrievable through standard ARexx result handling where practical. Streaming operations require defined cancellation. The command syntax will be versioned for script compatibility.
