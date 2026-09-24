# Native transcript renderer

The first transcript renderer draws directly into the window RastPort. It performs pixel-width word wrapping using the active Amiga font, clears only the conversation region, and keeps rendering independent of provider/session logic.

The renderer is deliberately small and native. It does not require MUI or a browser engine.

This first pass establishes redraw and wrapping. Scrolling state exists but will be refined together with scrollbar/keyboard input; the current implementation should not yet be considered the final scroll model.

The next pass connects redraw to refresh/resize and streamed chunk events, then adds proper viewport line calculation so auto-follow and manual scrollback coexist.


## Scroll interaction

The GUI now reserves a native vertical GadTools scroller and accepts raw cursor up/down keys for transcript navigation. Manual upward navigation disables follow mode; returning to the live edge can re-enable it. The next refinement will calculate wrapped visual-line totals and bind the scroller pot/body precisely to the viewport rather than using placeholder range values.


## Viewport metrics

The renderer now calculates total wrapped visual lines and visible viewport lines using the active RastPort font and current window width. The GadTools scroller is synchronized from those metrics. Follow mode places the viewport at the live edge as streamed text grows, while manual scroller movement sets an explicit top visual line.


## Wrapped-line viewport

Rendering and line counting now share the same visual-line iterator. The viewport offset is measured in wrapped display lines rather than physical newline-delimited lines, and drawing no longer mutates the stored top-line position. The text area also reserves space for the vertical scroller so wrapped text is not painted underneath it.
