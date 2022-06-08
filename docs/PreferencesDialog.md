# Preferences Dialog

![Preferences](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/Preferences.png)

The plugin has the following customizable Preference settings (default values are within parantheses):

### Auto-fill on Panel Focus (Checked)
When the Goto panel regains focus, the line and column fields in it will be refreshed with the current document's current cursor position. This is useful in situations when you only need to inspect the byte code at the current cursor position (see: <a href="#display-character-code-at-destination-checked">Display character code at destination</a>).

*This setting is effective only when the focus-changing click is on the panel's title bar or a blank area in the panel or the **Preferences** button*. This refresh is suppressed when the focus-changing click is within the **Goto Line/Column** input fields or on the **Go** button.

Uncheck this option if your workflow needs the Goto panel's line and column values to stay fixed regardless of changes in the current document's cursor position.

### Auto-fill on Document Tab Change (Checked)
When a different document becomes active either via a tab switch or file open or close actions, the line and column fields in the Goto panel will be refreshed with the newly active document's current cursor position.

In some situations -- when perhaps inspecting similar datafiles, it may be preferrable to have the line and column values stay fixed across the files. Uncheck this option for such workflows.

### Display character code at destination (Checked)
After navigating to the specified position in a document, the plugin displays a calltip. The calltip will list the current line number, character-based column, byte-based column, and the byte code of the character at the destination position. The calltip will disappear when the document cursor position shifts.
##### Calltip display for single-byte-based characters:
![Calltip](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/CalltipANSI.png)

##### Calltip display for multi-byte-based characters:
![Calltip](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/CalltipValidUTF-8.png)

In the UTF-8 byte sequence, the byte corresponding to the *Byte Column* position is within angle brackets. Also, note the difference in the *Char Column* and *Byte Column* values due to the multi-byte-based characters.

##### Calltip display for multi-byte-based characters with invalid UTF-8 byte sequence:
![Calltip](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/CalltipInvalidUTF-8.png)

The calltip can be handy to determine, for instance, if a character is a smart quote: “ (U+201C) or ” (U+201D) instead of the plain double quote: " (ASCII 34).

The calltip also provides supplemental highlighting of the cursor at the destination position (see: <a href="#highlight-character-at-destination-checked">Highlight character at destination</a>).

### Highlight character at destination (Checked)
After the cursor flash (see: <a href="#cursor-flash-duration-3-seconds">Cursor Flash duration</a>) is complete, the character at the destination position will be highlighted. This highlighting will disappear when the document cursor position shifts.

Uncheck this option if you do not wish to have the character highlighted at the destination position.

### Cursor is centered in the editor at destination (Checked)
When this option is checked, the cursor will try to position as close as possible to the center of the editor view area.

If the destination position is already within the prior view area, there will likely be no centering.

### Edge Buffer at destination (10)
*This setting is effective only when the <a href="#cursor-is-centered-in-the-editor-at-destination-checked">Centered Cursor </a> option is unchecked.*

When the destination character shows up with the cursor stuck at either the left or right edge of the Notepad++ document viewing area, it will be hard to spot the cursor and the character. Hence, when possible, a buffer margin near the edges is desirable.

For this setting, specify the number of characters to have as a buffer margin from either of the edges for the character at the destination position.

### Cursor Flash duration (3 seconds)
When the cursor is set at its default width of '1', it can be hard to spot the cursor at its new position. Especially when tired eyes have been staring at a sea of text on a widescreen monitor. To aid quick spotting, the cursor is briefly set to block mode at the destination position.

For this setting, specify the number of seconds to have the cursor flashing in block mode at the destination position.

---