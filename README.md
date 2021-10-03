# GotoLineCol Notepad++ Plugin

[Current Version: 2.1.1.0](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/VersionHistory.md)

A plugin for navigating to a specified line and column position in a file.

It is also handy for quickly inspecting byte-level content in files. The plugin will display the byte value at the document's current cursor position. In addition, for multi-byte-based characters in documents with Unicode-based encoding, the plugin will display the Unicode code point and its corresponding UTF-8 byte sequence (see: [Display character code at destination](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md#display-character-code-at-destination-checked)).

By default, the plugin uses byte-based positioning to navigate to the specified column.

## Plugin Panel

![GotoLineCol Panel](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/PanelBytePos.png)

The plugin can also be configured to use character-based positioning to navigate to the specified column.

![GotoLineCol Panel](https://raw.githubusercontent.com/shriprem/Goto-Line-Col-NPP-Plugin/master/images/PanelCharPos.png)

#### Spin controls:
The spin controls on the line and column fields provide quick navigation between adjacent lines or characters. The spin controls can be especially useful when inspecting character byte values (see: [Display character code at destination](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md#display-character-code-at-destination-checked)).

[*Since the line numbers increase downwards in a document, the spin control's down arrow increments the line or column number; and the up arrow decrements the line or column number. This orientation is a reversal of the typical spin control behavior in Windows; but it aligns with the document layout.*]

---

#### See also:
1. [Preferences Dialog](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/PreferencesDialog.md)

2. [Command Line Options](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/CommandLineOptions.md)

3. [Dark Mode Rendering](https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/DarkModeUI.md)

4. <a href="https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/docs/FAQs.md">Frequently Asked Questions</a>

5. <a href="https://github.com/shriprem/Goto-Line-Col-NPP-Plugin/blob/master/VersionHistory.md">Version History</a>

