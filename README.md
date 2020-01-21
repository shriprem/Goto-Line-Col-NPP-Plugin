# GotoLineCol Notepad++ Plugin

A plugin for navigating to a specified line and column position in a file. It is handy for manually inspecting content in fixed-width format data files.

![GotoLineCol Panel](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/Panel.png)

## Preferences

![Preferences](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/Preferences.png)
##### Preferences Dialog

The plugin has the following customizable Preference settings (default values within parantheses):

### Auto-fill on Panel Focus (Checked)
When the Goto panel regains focus, the line and column fields in it will be refreshed with the current document's current cursor position. This will be useful in situations when you only need to peek at the hex code value of the character at the current cursor position (see: <a href="#display-character-code-at-destination-checked">Display character code at destination</a>).

*This setting is effective only when the focus-changing click is on the panel's title bar or a blank area in the panel or the **Preferences** button*. This refresh is suppressed when the focus-changing click is within the **Goto Line/Column** input fields or on the **Go** button.

Uncheck this option if your workflow needs the Goto panel's line and column values to stay fixed regardless of changes in the current document's cursor position.

### Auto-fill on Document Tab Change (Checked)
When a different document becomes active either via a tab switch or file open or close, the line and column fields in the Goto panel will be refreshed with the newly active document's current cursor position.

In some situations -- when perhaps inspecting similar datafiles, it may be preferrable to have the line and column values stay fixed across the files. Uncheck this option for such workflows.

### Display character code at destination (Checked)
After navigating to the specified position, the plugin displays a calltip. The calltip will list the current line number, column position and the hex code value of the character at the destination position. The calltip will disappear when the document cursor position shifts.

![Calltip](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/Calltip.png)
##### Sample Calltip display

*The hex code value display is designed to work on files with ANSI encoding (or other single-byte character encodings)*. This can be handy to check, say if a character is a fancy quote: “ (ASCII 147) or ” (ASCII 148) instead of the plain double quote: " (ASCII 34).

The calltip also provides supplemental highlighting of the cursor at the destination position (see: <a href="#highlight-character-at-destination-checked">Highlight character at destination</a>).

### Highlight character at destination (Checked)
After the cursor flash (see: <a href="#cursor-flash-duration-3-seconds">Cursor Flash duration</a>) is complete, the character at the destination position will be highlighted. This highlighting will disappear when the document cursor position shifts.

Uncheck this option if you do not wish to have the character highlighted at the destination position.

### Expand TABS for column value computation (Unchecked)
When this option is checked, all TAB characters on the destination line will be counted using their expanded width -- a number specified in Notepad++ Preferences/Language section. In fact, Notepad++ also expands TABs in its column computation.

However, if you are viewing files with fixed-width format data, you may want to leave this option unchecked.

### Cursor is centered in the editor at destination (Checked)
When this option is checked, the cursor will try to position as close as possible to the center of the editor view area.

If the destination position is already within the prior view area, there will likely be no centering.

### Edge Buffer at destination (10)
*This setting is effective only when the <a href="#cursor-is-centered-in-the-editor-at-destination-checked">Centered Cursor </a> option is unchecked.*

When the destination character shows up with the cursor stuck at either the left or right edge of the Notepad++ document viewing area, it will be hard to spot the cursor and the character. Hence a buffer margin near the edges, when possible, is desirable.

For this setting, specify the number of characters to have as a buffer margin from either of the edges for the character at the destination position.

### Cursor Flash duration (3 seconds)
When the cursor is set at its default width of '1', it can be hard to spot the cursor at its new position. Especially when tired eyes have been staring at a sea of text on a widescreen monitor. To aid quick spotting, the cursor is briefly set to block mode at the destination position.

For this setting, specify the number of seconds to have the cursor flashing in block mode at the destination position.
