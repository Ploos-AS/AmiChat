# Configuration and secrets

AmiChat separates ordinary preferences from credentials.

Public configuration may contain provider id, model and endpoint override. `AmiChat_ConfigSavePublic()` deliberately never serializes the API key.

API keys are held in memory only by this layer. Replacing or destroying a key wipes its allocated buffer before release.

This is the baseline for the Amiga configuration UI and ARexx interface: commands may set credentials for the current process, but history/export/logging code must never expose them.

Future platform-specific secret storage can sit behind a separate credential backend. It must not weaken the default rule that conversation files are credential-free.
