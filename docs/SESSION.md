# Runtime session

`AmiChatSession` is the central runtime object intended to be shared by the native GUI and the `AMICHAT` ARexx port.

It owns runtime configuration, the active provider instance, core context and current conversation. The transport is supplied by the platform layer.

Typical flow:

1. create session with a transport
2. set provider/model/credential fields through the config object
3. apply configuration
4. send prompts through the session
5. consume streaming output while replies are persisted into conversation history

Changing provider configuration rebuilds the provider adapter without exposing protocol details to UI or ARexx code.

A new conversation replaces the current history but leaves provider configuration intact.
